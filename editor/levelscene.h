#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <QGraphicsScene>
#include <vector>

#include "Object.h"

class LevelScene: public QGraphicsScene {
    Q_OBJECT

private:
    int gridWidth;
    int gridHeight;
    std::vector<Object>& objects;
    QMap<QGraphicsItem*, Object*> objectMap;

    QGraphicsItem* selectedItem;
    QPointF originalItemPos;

    int ducksCount;
    ObjectType objectTypeToAdd;

public:
    LevelScene(QObject* parent, std::vector<Object>& objects);
    ~LevelScene() override = default;

    void deleteObjectAt(const QPointF& position);
    void addNewObject(ObjectType type, QPointF pos);
    void addObjectInMap(const Object& object, bool addInList);
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    // void toggleAddingObject(ObjectType type);
    void selectObjectType(ObjectType type);

    int getMapWidth() const;
    int getMapHeight() const;


    void clearAll();
    // Se encarga de cargar un mapa del tamaño pasado por parametro.
    // Cargara en el mapa los objetos de la lista objects, que ya se tiene la referencia en esta
    // clase.
    void loadMap(int mapWidth, int mapHeight);
    void newMap();
    void drawBackground(QPainter* painter, const QRectF& rect) override;
    // void zoom(double factor);
    bool enoughDucks() const;
    bool isEmptyPosition(QRectF itemRect);


signals:
    void addingObjectChanged(ObjectType type);
    void resizeView();
};

#endif  // LEVELSCENE_H
