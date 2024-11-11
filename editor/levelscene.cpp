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

LevelScene::LevelScene(QObject *parent, int width, int heigth)
        : QGraphicsScene(parent), selectedItem(nullptr) {
    setSceneRect(0, 0, width*PixelSize, heigth*PixelSize);
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
        selectedItem = nullptr;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}

void LevelScene::addObject(const Object& object) {
    QPixmap icon(object.icon);
    QPixmap iconScaled = icon.scaled(object.width* PixelSize, object.heigth * PixelSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    auto* item = new QGraphicsPixmapItem(iconScaled);

    item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setFlag(QGraphicsItem::ItemIsSelectable);

    auto viewCenter = this->views().first()->viewport()->rect().center();
    QPointF sceneCenter = this->views().first()->mapToScene(viewCenter);
    qreal x = std::round(sceneCenter.x() / PixelSize) * PixelSize;
    qreal y = std::round(sceneCenter.y() / PixelSize) * PixelSize;
    item->setPos(x, y);

    addItem(item);

    auto *itemAction = qobject_cast<QAction*>(sender());
    if (itemAction) {
        itemAction->setChecked(false);
    }
}

void LevelScene::drawBackground(QPainter* painter, const QRectF& rect) {
    QPen pen(Qt::lightGray);
    painter->setPen(pen);

    for (qreal x = std::floor(rect.left() / PixelSize) * PixelSize; x < rect.right(); x += PixelSize) {
        painter->drawLine(QPointF(x, rect.top()), QPointF(x, rect.bottom()));
    }
    for (qreal y = std::floor(rect.top() / PixelSize) * PixelSize; y < rect.bottom(); y += PixelSize) {
        painter->drawLine(QPointF(rect.left(), y), QPointF(rect.right(), y));
    }
}
