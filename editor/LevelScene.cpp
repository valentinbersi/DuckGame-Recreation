#include "LevelScene.h"

#include <QAction>
#include <QDrag>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMimeData>
#include <cmath>
#include <list>

#include "EditorConstants.h"

#define MIN_DUCKS 4

LevelScene::LevelScene(QObject* parent, std::list<Object>& objects):
        QGraphicsScene(parent),
        objects(objects),
        selectedItem(nullptr),
        ducksCount(0),
        objectTypeToAdd(UNKNOWN) {
    setBackgroundBrush(Qt::NoBrush);
    gridWidth = DEFAULT_WIDTH * PIXEL_SIZE;
    gridHeight = DEFAULT_HEIGHT * PIXEL_SIZE;
    setSceneRect(0, 0, gridWidth, gridHeight);
}

void LevelScene::deleteObjectAt(const QPointF& position) {
    auto* itemAtPosition = qgraphicsitem_cast<QGraphicsPixmapItem*>(items(position).value(0));
    if (!itemAtPosition)
        return;

    auto* object = objectsMap[itemAtPosition];
    if (object->type == DUCK)
        ducksCount--;

    objects.remove(*object);
    objectsMap.remove(itemAtPosition);
    removeItem(itemAtPosition);
    delete itemAtPosition;
}

bool LevelScene::enoughDucks() const { return ducksCount >= MIN_DUCKS; }

bool LevelScene::isEmptyPosition(QRectF itemRect) {
    for (QGraphicsItem* currentItem: items()) {
        if (selectedItem == currentItem)
            continue;

        QRectF currentItemRect = currentItem->sceneBoundingRect();
        // el +- 0.5 es por un borde invisible que el QT agrega en los Pixmap
        if (!(itemRect.right() <= currentItemRect.left() + 0.5 ||
              itemRect.left() >= currentItemRect.right() - 0.5 ||
              itemRect.bottom() <= currentItemRect.top() + 0.5 ||
              itemRect.top() >= currentItemRect.bottom() - 0.5)) {
            return false;
        }
    }
    return true;
}

void LevelScene::insertObjectInMap(const Object& object, bool addInList) {
    QPointF topLeftPos = object.getBoundingPos();
    QPointF itemPos(int(topLeftPos.x()) * PIXEL_SIZE, int(topLeftPos.y()) * PIXEL_SIZE);
    QSizeF itemSize(object.size.width() * PIXEL_SIZE, object.size.height() * PIXEL_SIZE);
    QRectF itemRect(itemPos, itemSize);

    if (!isEmptyPosition(itemRect))
        return;

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
        //        auto it = std::find(objects.begin(), objects.end(), object);
        //        if (it != objects.end()) {
        //            storedObject = &(*it);
        //        }
        storedObject = (Object*)(&object);
    }

    objectsMap[item] = storedObject;
    if (object.type == DUCK)
        ducksCount++;

    /** ESTO CAPAZ PODRIA HACERLO APARTE */
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
        insertObjectInMap(object, false);
    }
}


void LevelScene::addNewObject(ObjectType type, QPointF pos) {
    QPointF centerPos(std::round(pos.x() / PIXEL_SIZE), std::round(pos.y() / PIXEL_SIZE));
    if (centerPos.x() < 1 || centerPos.y() < 1)
        return;

    Object newObject(type);
    newObject.setCenterPosition(centerPos, false);
    insertObjectInMap(newObject, true);

    auto* itemAction = qobject_cast<QAction*>(sender());
    if (itemAction)
        itemAction->setChecked(false);
}

void LevelScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::RightButton) {
        isDeletingObject = true;
        deleteObjectAt(event->scenePos());
        emit requestDragModeChange(QGraphicsView::NoDrag);
        return;
    }

    if (event->button() == Qt::LeftButton && objectTypeToAdd != UNKNOWN) {
        isAddingObject = true;
        addNewObject(objectTypeToAdd, event->scenePos());
        emit requestDragModeChange(QGraphicsView::NoDrag);
        return;
    }

    QGraphicsItem* item = itemAt(event->scenePos(), QTransform());
    if (item && item->flags() & QGraphicsItem::ItemIsMovable) {
        selectedItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
        originalItemPos = selectedItem->pos();
    }

    QGraphicsScene::mousePressEvent(event);
}

void LevelScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    if (isAddingObject && objectTypeToAdd != UNKNOWN && event->buttons() & Qt::LeftButton)
        addNewObject(objectTypeToAdd, event->scenePos());

    if (isDeletingObject && event->buttons() & Qt::RightButton)
        deleteObjectAt(event->scenePos());

    if (selectedItem)
        selectedItem->setPos(event->scenePos() -
                             QPointF(selectedItem->boundingRect().width() / 2,
                                     selectedItem->boundingRect().height() / 2));

    QGraphicsScene::mouseMoveEvent(event);
}

void LevelScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        isAddingObject = false;
        emit requestDragModeChange(QGraphicsView::ScrollHandDrag);
    }
    if (event->button() == Qt::RightButton) {
        isDeletingObject = false;
        emit requestDragModeChange(QGraphicsView::ScrollHandDrag);
    }

    if (selectedItem) {
        QPointF itemPos = selectedItem->pos();

        /** Alineacion de la posicion a la grilla ¿podria tener un metodo para esto? */
        qreal alignedX = std::round(itemPos.x() / PIXEL_SIZE) * PIXEL_SIZE;
        qreal alignedY = std::round(itemPos.y() / PIXEL_SIZE) * PIXEL_SIZE;
        if (itemPos.x() < alignedX - PIXEL_SIZE / 2.0)
            alignedX -= PIXEL_SIZE;
        if (itemPos.y() < alignedY - PIXEL_SIZE / 2.0)
            alignedY -= PIXEL_SIZE;

        QPointF itemPosAligned(alignedX, alignedY);

        QRectF itemRect(itemPosAligned, selectedItem->boundingRect().size() - QSizeF(1, 1));
        if (!isEmptyPosition(itemRect)) {
            selectedItem->setPos(originalItemPos);
            selectedItem = nullptr;
            return;
        }

        selectedItem->setPos(itemPosAligned);

        Object* obj = objectsMap[selectedItem];
        QPointF newPos(int(itemPosAligned.x()) / PIXEL_SIZE, int(itemPosAligned.y()) / PIXEL_SIZE);
        obj->setCenterPosition(newPos, true);

        selectedItem = nullptr;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void LevelScene::drawBackground(QPainter* painter, const QRectF&) {
    painter->save();

    painter->setBrush(Qt::NoBrush);
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

int LevelScene::getMapWidth() const { return gridWidth / (int)PIXEL_SIZE; }

int LevelScene::getMapHeight() const { return gridHeight / (int)PIXEL_SIZE; }

void LevelScene::clearAll() {
    objectsMap.clear();
    clear();
    objects.clear();
    ducksCount = 0;
}
