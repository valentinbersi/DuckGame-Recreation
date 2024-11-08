#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <QGraphicsScene>

class LevelScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit LevelScene(QObject *parent = nullptr);
    ~LevelScene() override = default;
    void addCustomRect();
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
};

#endif  // LEVELSCENE_H
