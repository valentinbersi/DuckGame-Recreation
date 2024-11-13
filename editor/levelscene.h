#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <QGraphicsScene>

#include "Object.h"

class LevelScene : public QGraphicsScene {
    Q_OBJECT

private:
    int gridWidth;
    int gridHeight;
    QGraphicsItem* selectedItem;
    std::vector<Object>& objects;

public:
    LevelScene(QObject* parent, int width, int height, std::vector<Object>& objects);
    ~LevelScene() override = default;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void addObject(const Object& object);
    void drawBackground(QPainter* painter, const QRectF& rect) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif  // LEVELSCENE_H
