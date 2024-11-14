#include "levelscene.h"

#include <QAction>
#include <QDebug>
#include <QDrag>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMimeData>
#include <cmath>


#define PixelSize 15

LevelScene::LevelScene(QObject *parent, int width, int height, std::vector<Object>& objects)
        : QGraphicsScene(parent), selectedItem(nullptr), objects(objects) {
    gridWidth = width*PixelSize;
    gridHeight = height*PixelSize;
    setSceneRect(0, 0, gridWidth, gridHeight);
}

void LevelScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    qDebug() << "Clic en la escena en: " << event->scenePos();

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
            obj->setPos(x/PixelSize,y/PixelSize);
        }

        selectedItem = nullptr;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void LevelScene::addObject(const Object& object) {
    QPixmap icon(object.icon);
    QPixmap iconScaled = icon.scaled(object.width* PixelSize, object.height * PixelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    auto* item = new QGraphicsPixmapItem(iconScaled);
    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemIsSelectable);

    auto viewCenter = this->views().first()->viewport()->rect().center();
    QPointF sceneCenter = this->views().first()->mapToScene(viewCenter);
    qreal x = std::round(sceneCenter.x() / PixelSize) * PixelSize;
    qreal y = std::round(sceneCenter.y() / PixelSize) * PixelSize;
    item->setPos(x, y);

    addItem(item);
    objects.push_back(object);
    item->setData(0, QVariant::fromValue(&objects.back()));

    auto *itemAction = qobject_cast<QAction*>(sender());
    if (itemAction) {
        itemAction->setChecked(false);
    }
}

void LevelScene::drawBackground(QPainter* painter, const QRectF&) {
    painter->save();
    QPen pen(Qt::lightGray);
    painter->setPen(pen);

    // Tamaño total del área de visualización
    qreal viewWidth = gridWidth; // Cambia esto a un valor que represente el ancho total deseado
    qreal viewHeight = gridHeight; // Cambia esto a un valor que represente el alto total deseado

    // Dibuja las líneas verticales
    for (qreal x = 0; x <= viewWidth; x += PixelSize) {
        painter->drawLine(QPointF(x, 0), QPointF(x, viewHeight));
    }

    // Dibuja las líneas horizontales
    for (qreal y = 0; y <= viewHeight; y += PixelSize) {
        painter->drawLine(QPointF(0, y), QPointF(viewWidth, y));
    }
    painter->restore();
}
