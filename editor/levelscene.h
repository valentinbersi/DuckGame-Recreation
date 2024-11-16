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

    bool addingObject;
    ObjectType objectTypeToAdd;

public:
    LevelScene(QObject* parent, int width, int height, std::vector<Object>& objects);
    ~LevelScene() override = default;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    static Object createObject(ObjectType type);
    void addObject(ObjectType type);
    void drawBackground(QPainter* painter, const QRectF& rect) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void toggleAddingObject(ObjectType type);
    void deleteObjectAt(const QPointF& position);
    void clearAll();

signals:
    void addingObjectChanged(ObjectType type, bool isAdding);
};

#endif  // LEVELSCENE_H
