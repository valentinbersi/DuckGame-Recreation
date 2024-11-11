#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <QGraphicsScene>

#include "Object.h"

class LevelScene : public QGraphicsScene {
    Q_OBJECT

private:
    //    int gridHeigth;
    //    int gridWidth;
    QGraphicsItem* selectedItem;

public:
    LevelScene(QObject* parent, int width, int heigth);
    ~LevelScene() override = default;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void addObject(const Object& object);
    void drawBackground(QPainter* painter, const QRectF& rect) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif  // LEVELSCENE_H
