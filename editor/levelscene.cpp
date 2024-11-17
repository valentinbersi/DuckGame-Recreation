#include "levelscene.h"
#include "ObjectConstants.h"

#include <QAction>
#include <QDrag>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMimeData>
#include <cmath>


#define PixelSize 15

LevelScene::LevelScene(QObject *parent, int width, int height, std::vector<Object>& objects)
        : QGraphicsScene(parent), selectedItem(nullptr), objects(objects), addingObject(false), objectTypeToAdd(UNKNOWN) {
    gridWidth = width*PixelSize;
    gridHeight = height*PixelSize;
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

void LevelScene::addObject(ObjectType type, QPointF pos) {
    Object newObject = createObject(type);
    QPixmap icon(newObject.icon);
    QPixmap iconScaled = icon.scaled(newObject.size.width() * PixelSize, newObject.size.height() * PixelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    auto* item = new QGraphicsPixmapItem(iconScaled);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemIsSelectable);

    QPointF topLeftPos(
            pos.x() - (newObject.size.width() / 2) * PixelSize,
            pos.y() - (newObject.size.height() / 2) * PixelSize);

    int x = (int(topLeftPos.x()) / PixelSize) * PixelSize;
    int y = (int(topLeftPos.y()) / PixelSize) * PixelSize;
    item->setPos(x, y);

    newObject.setCenterPosition(
            QPointF(x / PixelSize + newObject.size.width() / 2,
                    y / PixelSize + newObject.size.height() / 2));

    addItem(item);
    objects.push_back(newObject);
    item->setData(0, QVariant::fromValue(&objects.back()));

    QRectF currentRect = sceneRect();

    //QRectF objectRect(item->pos(), QSizeF(newObject.size.width() * PixelSize, newObject.size.height() * PixelSize));
    QPointF objectTopLeft = item->scenePos();  // Convertir a coordenadas globales
    QRectF objectRect(objectTopLeft, QSizeF(newObject.size.width() * PixelSize, newObject.size.height() * PixelSize));

    qDebug() << "Current sceneRect:" << currentRect;
    qDebug() << "Object rect:" << objectRect;
    if (!currentRect.contains(objectRect)) {
        QRectF expandedRect = currentRect.united(objectRect); // Unir los rectángulos
        setSceneRect(expandedRect); // Actualizar la escena
        qDebug() << "Expanded rect:" << expandedRect;
    }

    auto *itemAction = qobject_cast<QAction*>(sender());
    if (itemAction) {
        itemAction->setChecked(false);
    }
}

void LevelScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    qDebug() << "Clic en la escena en: " << event->scenePos();

    if (event->button() == Qt::RightButton) {
        deleteObjectAt(event->scenePos());
        return;
    }

    if (addingObject && objectTypeToAdd != UNKNOWN) {
        QPointF pos = event->scenePos();
        addObject(objectTypeToAdd, pos);
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
        int x = int(pos.x()) / PixelSize * PixelSize;
        int y = int(pos.y()) / PixelSize * PixelSize;
        selectedItem->setPos(x, y);

        auto* obj = selectedItem->data(0).value<Object*>();
        if (obj) {
            QPointF centerPos(
                    (x + (obj->size.width() * PixelSize) / 2) / PixelSize,
                    (y + (obj->size.height() * PixelSize) / 2) / PixelSize
            );
            obj->setCenterPosition(centerPos);
        }

        selectedItem = nullptr;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

Object LevelScene::createObject(ObjectType type) {
    switch (type) {
        case PLATFORM:
            return {PLATFORM, PLATFORM_HEIGHT, PLATFORM_WIDTH, PLATFORM_ICON};
        case DUCK:
            return {DUCK, DUCK_HEIGHT, DUCK_WIDTH, DUCK_ICON};
        case ARMAMENT:
            return {ARMAMENT, ARMAMENT_HEIGHT, ARMAMENT_WIDTH, ARMAMENT_ICON};
        case BOX:
            return {BOX, BOX_HEIGHT, BOX_WIDTH, BOX_ICON};
        default:
            qWarning() << "Tipo de objeto desconocido";
            return {UNKNOWN, 0, 0, ""};
    }
}

void LevelScene::drawBackground(QPainter* painter, const QRectF&) {
    painter->save();
    QPen pen(Qt::lightGray);
    painter->setPen(pen);

    qreal viewWidth = gridWidth;
    qreal viewHeight = gridHeight;

    for (qreal x = 0; x <= viewWidth; x += PixelSize) {
        painter->drawLine(QPointF(x, 0), QPointF(x, viewHeight));
    }

    for (qreal y = 0; y <= viewHeight; y += PixelSize) {
        painter->drawLine(QPointF(0, y), QPointF(viewWidth, y));
    }
    painter->restore();
}

void LevelScene::toggleAddingObject(ObjectType type) {
    if (addingObject && objectTypeToAdd == type){
        addingObject = false;
        objectTypeToAdd = UNKNOWN;
    } else {
        addingObject = true;
        objectTypeToAdd = type;
    }

    emit addingObjectChanged(objectTypeToAdd, addingObject);
}

void LevelScene::clearAll() {
    clear();
    objects.clear();
}