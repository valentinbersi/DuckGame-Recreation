#include "levelscene.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

LevelScene::LevelScene(QObject *parent)
        : QGraphicsScene(parent) {
}

void LevelScene::addCustomRect() {
    addRect(0,0,100,100, QPen(Qt::black), QBrush(Qt::green));
}

void LevelScene::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    qDebug() << "Clic en la escena en: " << event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}