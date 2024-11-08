#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <QGraphicsScene>

class LevelScene : public QGraphicsScene
{
    Q_OBJECT

private:
//    int gridHeigth;
//    int gridWidth;

public:
    explicit LevelScene(QObject *parent = nullptr);
    ~LevelScene() override = default;
    void addCustomRect();
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void addPlatform();
    void drawBackground(QPainter* painter, const QRectF& rect) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif  // LEVELSCENE_H
