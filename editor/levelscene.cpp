#include "levelscene.h"

#include <QAction>
#include <QDrag>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMimeData>
#include <cmath>


#define PIXEL_SIZE 15
#define DEFAULT_WIDTH 50
#define DEFAULT_HEIGHT 50

LevelScene::LevelScene(QObject *parent, std::vector<Object>& objects)
        : QGraphicsScene(parent), selectedItem(nullptr), objects(objects), addingObject(false), objectTypeToAdd(UNKNOWN) {
    gridWidth = DEFAULT_WIDTH * PIXEL_SIZE;
    gridHeight = DEFAULT_HEIGHT * PIXEL_SIZE;
    setSceneRect(0, 0, gridWidth, gridHeight);
}

void LevelScene::deleteObjectAt(const QPointF& position) {
    QList<QGraphicsItem*> itemsAtPosition = items(position);

    for (auto* item : itemsAtPosition) {
        auto* pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(item);
        if (pixmapItem) {
            QVariant objectData = pixmapItem->data(0);
            if (objectData.isValid()) {
                Object* object = objectData.value<Object*>();
                if (object) {
                    auto it = std::find_if(objects.begin(), objects.end(), [object](const Object& obj) {
                        return object == &obj;
                    });
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

void LevelScene::addObjectInMap(Object object) {
    QPixmap icon(object.icon);
    QPixmap iconScaled =
            icon.scaled(object.size.width() * PIXEL_SIZE, object.size.height() * PIXEL_SIZE,
                        Qt::KeepAspectRatio, Qt::SmoothTransformation);

    auto* item = new QGraphicsPixmapItem(iconScaled);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemIsSelectable);

    QPointF topLeftPos((object.centerPos.x() - (object.size.width() / 2)) * PIXEL_SIZE,
                       (object.centerPos.y() - (object.size.height() / 2)) * PIXEL_SIZE);
    int x = (int(topLeftPos.x()) / PIXEL_SIZE) * PIXEL_SIZE;
    int y = (int(topLeftPos.y()) / PIXEL_SIZE) * PIXEL_SIZE;
    item->setPos(x, y);

    addItem(item);
    item->setData(0, QVariant::fromValue(&objects.back()));

    // esto capaz podria manejarlo en otro lado ¿?
    QRectF objectRect(item->scenePos(),
                      QSizeF(object.size.width() * PIXEL_SIZE,
                             object.size.height() * PIXEL_SIZE));
    QRectF currentRect = sceneRect();

    if (!currentRect.contains(objectRect)) {
        QRectF expandedRect = currentRect.united(objectRect);
        setSceneRect(expandedRect);
        gridWidth = expandedRect.width();
        gridHeight = expandedRect.height();
    }
}

void LevelScene::newMap() {
    clearAll();
    gridWidth = DEFAULT_WIDTH * PIXEL_SIZE;
    gridHeight = DEFAULT_HEIGHT * PIXEL_SIZE;
}

void LevelScene::loadMap(int mapWidth, int mapHeight) {
    qDebug() << "width loadMap: " << mapWidth << ", height loadMap: " << mapHeight;
    setSceneRect(0, 0, mapWidth * PIXEL_SIZE, mapHeight * PIXEL_SIZE);
    qDebug() << "width SceneRect: " << sceneRect().width() << ", height lSceneRect: " << sceneRect().height();
    gridWidth = mapWidth * PIXEL_SIZE;
    gridHeight = mapHeight * PIXEL_SIZE;
    qDebug() << "gridWidth: " << gridWidth << ", gridHeight: " << gridHeight;
    for (const auto& object : objects) {
        addObjectInMap(object);
    }
}

void LevelScene::addNewObject(ObjectType type, QPointF pos) {
    Object newObject(type);
    newObject.setCenterPosition(QPointF((int)(pos.x()) / PIXEL_SIZE + newObject.size.width() / 2,
                                        (int)(pos.y()) / PIXEL_SIZE + newObject.size.height() / 2));
    addObjectInMap(newObject);
    objects.push_back(newObject);

    auto *itemAction = qobject_cast<QAction*>(sender());
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
        selectedItem->setPos(event->scenePos() - QPointF(selectedItem->boundingRect().width() / 2, selectedItem->boundingRect().height() / 2));
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
            QPointF centerPos(
                    (x + (obj->size.width() * PIXEL_SIZE) / 2) / PIXEL_SIZE,
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

void LevelScene::clearAll() {
    clear();
    objects.clear();
}