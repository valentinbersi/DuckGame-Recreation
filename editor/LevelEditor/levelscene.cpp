#include "levelscene.h"

#include <QAction>
#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <cmath>

#define PixelSize 15

LevelScene::LevelScene(QObject *parent)
        : QGraphicsScene(parent) {}

void LevelScene::addCustomRect() {
    addRect(0,0,100,100, QPen(Qt::black), QBrush(Qt::green));
}

void LevelScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    qDebug() << "Clic en la escena en: " << event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void LevelScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsScene::mouseReleaseEvent(event);
    for (QGraphicsItem* item : selectedItems()) {
        if (item->flags() & QGraphicsItem::ItemIsMovable) {
            QPointF pos = item->pos();
            int x = int(pos.x()) / PixelSize * PixelSize;
            int y = int(pos.y()) / PixelSize * PixelSize;
            item->setPos(x, y);
        }
    }
}

void LevelScene::addPlatform() {
    auto* platform = new QGraphicsRectItem(0, 0, PixelSize*2, PixelSize*2);
    platform->setBrush(QBrush(Qt::blue));

    platform->setFlag(QGraphicsItem::ItemIsMovable);
    platform->setFlag(QGraphicsItem::ItemIsSelectable);

    auto viewCenter = this->views().first()->viewport()->rect().center();
    QPointF sceneCenter = this->views().first()->mapToScene(viewCenter);
    qreal x = std::round(sceneCenter.x() / PixelSize) * PixelSize;
    qreal y = std::round(sceneCenter.y() / PixelSize) * PixelSize;
    platform->setPos(x, y);

    addItem(platform);

    auto *platformAction = qobject_cast<QAction*>(sender());
    if (platformAction) {
        platformAction->setChecked(false);
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
