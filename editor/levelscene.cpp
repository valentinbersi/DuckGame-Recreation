#include "levelscene.h"
#include "EditorConstants.h"

#include <QAction>
#include <QDrag>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMimeData>
#include <cmath>
#include <vector>

LevelScene::LevelScene(QObject* parent, std::vector<Object>& objects):
        QGraphicsScene(parent),
        selectedItem(nullptr),
        objects(objects),
        ducksCount(0),
        objectTypeToAdd(UNKNOWN) {
    gridWidth = DEFAULT_WIDTH * PIXEL_SIZE;
    gridHeight = DEFAULT_HEIGHT * PIXEL_SIZE;
    setSceneRect(0, 0, gridWidth, gridHeight);
}

void LevelScene::deleteObjectAt(const QPointF& position) {
    QList<QGraphicsItem*> itemsAtPosition = items(position);

    for (auto* item: itemsAtPosition) {
        auto* pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(item);
        if (pixmapItem) {
            QVariant objectData = pixmapItem->data(0);
            if (objectData.isValid()) {
                Object* object = objectData.value<Object*>();
                if (object) {
                    if (object->type == DUCK)
                        ducksCount--;

                    auto it = std::find_if(objects.begin(), objects.end(),
                                           [object](const Object& obj) { return object == &obj; });
                    if (it != objects.end()) {
                        objects.erase(it);
                    }
                }
            }

            removeItem(pixmapItem);
            delete pixmapItem;
            break;
        }
    }
}

bool LevelScene::enoughDucks() const { return ducksCount >= 1; }

void LevelScene::addObjectInMap(const Object& object) {
    if (object.type == DUCK && ducksCount >= 4)
        return;

    auto* item = new QGraphicsPixmapItem(object.icon);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemIsSelectable);

    QPointF topLeftPos = object.getBoundingPos();
    int x_item = (int(topLeftPos.x()) * PIXEL_SIZE);
    int y_item = (int(topLeftPos.y()) * PIXEL_SIZE);
    item->setPos(x_item, y_item);
    qDebug() << item->pixmap().height() << item->pixmap().width();
    addItem(item);
    item->setData(0, QVariant::fromValue(object));
    if (object.type == DUCK)
        ducksCount++;

    QRectF objectRect(item->scenePos(),
                      QSizeF(object.size.width() * PIXEL_SIZE, object.size.height() * PIXEL_SIZE));
    QRectF currentRect = sceneRect();

    if (!currentRect.contains(objectRect)) {
        QRectF expandedRect = currentRect.united(objectRect);
        setSceneRect(expandedRect);
        gridWidth = expandedRect.width();
        gridHeight = expandedRect.height();
        emit resizeView();
    }
}

void LevelScene::newMap() {
    clearAll();
    gridWidth = DEFAULT_WIDTH * PIXEL_SIZE;
    gridHeight = DEFAULT_HEIGHT * PIXEL_SIZE;
}

void LevelScene::loadMap(int mapWidth, int mapHeight) {
    setSceneRect(0, 0, mapWidth * PIXEL_SIZE, mapHeight * PIXEL_SIZE);
    gridWidth = mapWidth * PIXEL_SIZE;
    gridHeight = mapHeight * PIXEL_SIZE;
    for (const auto& object: objects) {
        addObjectInMap(object);
    }
}

void LevelScene::addNewObject(ObjectType type, QPointF pos) {
    Object newObject(type);
    newObject.setCenterPosition(QPointF((int)(pos.x()) / PIXEL_SIZE + newObject.size.width() / 2,
                                        (int)(pos.y()) / PIXEL_SIZE + newObject.size.height() / 2));
    addObjectInMap(newObject);
    objects.push_back(newObject);

    auto* itemAction = qobject_cast<QAction*>(sender());
    if (itemAction) {
        itemAction->setChecked(false);
    }
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
        QPointF pos = selectedItem->pos();
        int x = int(pos.x()) / PIXEL_SIZE * PIXEL_SIZE;
        int y = int(pos.y()) / PIXEL_SIZE * PIXEL_SIZE;
        selectedItem->setPos(x, y);

        auto* obj = selectedItem->data(0).value<Object*>();
        if (obj) {
            QPointF centerPos((x + (obj->size.width() * PIXEL_SIZE) / 2) / PIXEL_SIZE,
                              (y + (obj->size.height() * PIXEL_SIZE) / 2) / PIXEL_SIZE);
            obj->setCenterPosition(centerPos);
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

    for (qreal x = 0; x <= viewWidth; x += PIXEL_SIZE) {
        painter->drawLine(QPointF(x, 0), QPointF(x, viewHeight));
    }

    for (qreal y = 0; y <= viewHeight; y += PIXEL_SIZE) {
        painter->drawLine(QPointF(0, y), QPointF(viewWidth, y));
    }
    painter->restore();
}

void LevelScene::selectObjectType(ObjectType type) {
    if (objectTypeToAdd == type) {
        objectTypeToAdd = UNKNOWN;
    } else {
        objectTypeToAdd = type;
    }
    emit addingObjectChanged(objectTypeToAdd);
}

int LevelScene::getMapWidth() const { return gridWidth / PIXEL_SIZE; }

int LevelScene::getMapHeight() const { return gridHeight / PIXEL_SIZE; }

void LevelScene::clearAll() {
    clear();
    objects.clear();
}
