#include "levelscene.h"

#include <QAction>
#include <QDrag>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMimeData>
#include <cmath>
#include <vector>

#include "EditorConstants.h"

LevelScene::LevelScene(QObject* parent, std::vector<Object>& objects):
        QGraphicsScene(parent),
        objects(objects),
        selectedItem(nullptr),
        ducksCount(0),
        objectTypeToAdd(UNKNOWN) {
    gridWidth = DEFAULT_WIDTH * PIXEL_SIZE;
    gridHeight = DEFAULT_HEIGHT * PIXEL_SIZE;
    setSceneRect(0, 0, gridWidth, gridHeight);
}

void LevelScene::deleteObjectAt(const QPointF& position) {
    QGraphicsItem* itemAtPosition = items(position).value(0);

    if (itemAtPosition) {
        auto* pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(itemAtPosition);
        if (pixmapItem) {
            QVariant objectData = pixmapItem->data(0);
            if (objectData.isValid()) {
                auto object = objectData.value<Object>();
                if (object.type == DUCK) ducksCount--;

                auto it = std::find_if(objects.begin(), objects.end(),
                                       [object](const Object& obj) { return object == obj; });
                if (it != objects.end())
                    objects.erase(it);
            }

            removeItem(pixmapItem);
            delete pixmapItem;
        }
    }
}

bool LevelScene::enoughDucks() const { return ducksCount == MIN_DUCKS; }

bool LevelScene::isEmptyPosition(QRectF itemRect) {
    for (QGraphicsItem* currentItem : items()) {
        if (selectedItem == currentItem)
            continue;

        QRectF currentItemRect = currentItem->sceneBoundingRect();
        // el +- 0.5 es por un borde invisible que el QT agrega en los Pixmap
        if (!(itemRect.right() <= currentItemRect.left() + 0.5 || itemRect.left() >= currentItemRect.right() - 0.5 ||
              itemRect.bottom() <= currentItemRect.top() + 0.5 || itemRect.top() >= currentItemRect.bottom() - 0.5 )) {
            return false;
        }
    }
    return true;
}

void LevelScene::addObjectInMap(const Object& object, bool addInList) {
    if (object.type == DUCK && ducksCount >= 4) return;

    QPointF topLeftPos = object.getBoundingPos();
    QPointF itemPos(int(topLeftPos.x()) * PIXEL_SIZE, int(topLeftPos.y()) * PIXEL_SIZE);
    QSizeF itemSize(object.size.width() * PIXEL_SIZE, object.size.height() * PIXEL_SIZE);
    QRectF itemRect(itemPos, itemSize);

    if (!isEmptyPosition(itemRect)) return;

    auto* item = new QGraphicsPixmapItem(object.icon);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemIsSelectable);
    item->setPos(itemPos);
    addItem(item);

    Object* storedObject = nullptr;
    if (addInList) {
        objects.push_back(object);
        storedObject = &objects.back();
    } else {
        auto it = std::find(objects.begin(), objects.end(), object);
        if (it != objects.end()) {
            storedObject = &(*it);
        }
    }

    if (storedObject) {
        objectMap[item] = storedObject;
    } else {
        qDebug() << "Error: no se pudo encontrar el objeto para asociarlo con el item.";
        delete item; // Limpiar si no se puede asociar correctamente
        return;
    }

    if (object.type == DUCK) ducksCount++;

    QRectF objectRect(item->scenePos(),
                      QSizeF(object.size.width() * PIXEL_SIZE, object.size.height() * PIXEL_SIZE));
    QRectF currentRect = sceneRect();

    if (!currentRect.contains(objectRect)) {
        QRectF expandedRect = currentRect.united(objectRect);
        setSceneRect(expandedRect);
        gridWidth = (int)expandedRect.width();
        gridHeight = (int)expandedRect.height();
        emit resizeView();
    }
}

void LevelScene::loadMap(int mapWidth, int mapHeight) {
    setSceneRect(0, 0, mapWidth * PIXEL_SIZE, mapHeight * PIXEL_SIZE);
    gridWidth = mapWidth * PIXEL_SIZE;
    gridHeight = mapHeight * PIXEL_SIZE;
    for (const auto& object: objects) {
        addObjectInMap(object, false);
    }
}



void LevelScene::addNewObject(ObjectType type, QPointF pos) {
    Object newObject(type);
    newObject.setCenterPosition(QPointF(std::round(pos.x() / PIXEL_SIZE), std::round(pos.y() / PIXEL_SIZE)), true);
    addObjectInMap(newObject, true);

    auto* itemAction = qobject_cast<QAction*>(sender());
    if (itemAction)
        itemAction->setChecked(false);
}

void LevelScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::RightButton) {
        deleteObjectAt(event->scenePos());
        return;
    }

    if (objectTypeToAdd != UNKNOWN) {
        QPointF pos = event->scenePos();
        addNewObject(objectTypeToAdd, pos);
        return;
    }

    QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
    if (item && item->flags() & QGraphicsItem::ItemIsMovable) {
        selectedItem = item;
        originalItemPos = selectedItem->pos();
    }

    QGraphicsScene::mousePressEvent(event);
}

void LevelScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (selectedItem) {
        selectedItem->setPos(event->scenePos() -
                             QPointF(selectedItem->boundingRect().width() / 2,
                                     selectedItem->boundingRect().height() / 2));
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void LevelScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (selectedItem) {
        QPointF itemPos = selectedItem->pos();
        QPointF itemPosAligned(int(itemPos.x()) / PIXEL_SIZE * PIXEL_SIZE,
                               int(itemPos.y()) / PIXEL_SIZE * PIXEL_SIZE);
        QRectF itemRect(itemPosAligned, selectedItem->boundingRect().size() - QSizeF(1,1));

        if (!isEmptyPosition(itemRect)){
            selectedItem->setPos(originalItemPos);
            selectedItem = nullptr;
            return;
        }

        selectedItem->setPos(itemPosAligned);

        auto it = objectMap.find(selectedItem);
        if (it != objectMap.end() && it.value()) {
            Object* objectMoved = it.value(); // Obtener el puntero al objeto asociado
            QPointF newCenterPos(int(itemPosAligned.x()) / PIXEL_SIZE,
                                 int(itemPosAligned.y()) / PIXEL_SIZE);
            objectMoved->setCenterPosition(newCenterPos, true);
        } else {
            qDebug() << "Error: no se encontró el objeto asociado al item.";
        }

        selectedItem = nullptr;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void LevelScene::drawBackground(QPainter* painter, const QRectF&) {
    painter->save();
    QPen pen(Qt::lightGray);
    painter->setPen(pen);

    qreal viewWidth = gridWidth;
    qreal viewHeight = gridHeight;

    for (qreal x = 0; x <= viewWidth; x += PIXEL_SIZE)
        painter->drawLine(QPointF(x, 0), QPointF(x, viewHeight));

    for (qreal y = 0; y <= viewHeight; y += PIXEL_SIZE)
        painter->drawLine(QPointF(0, y), QPointF(viewWidth, y));

    painter->restore();
}

void LevelScene::selectObjectType(ObjectType type) {
    if (objectTypeToAdd == type)
        objectTypeToAdd = UNKNOWN;
    else
        objectTypeToAdd = type;

    emit addingObjectChanged(objectTypeToAdd);
}

int LevelScene::getMapWidth() const { return gridWidth / PIXEL_SIZE; }

int LevelScene::getMapHeight() const { return gridHeight / PIXEL_SIZE; }

void LevelScene::clearAll() {
    clear();
    objects.clear();
    ducksCount = 0;
}
