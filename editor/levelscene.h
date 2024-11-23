#ifndef LEVELSCENE_H
#define LEVELSCENE_H

#include <QGraphicsScene>
#include <vector>

#include "Object.h"

#define MIN_DUCKS 4

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


    /**
     * Elimina el elemento en la posicion recibida.
     * Elimina el item de la escena (PixmapItem) y el Object como tal.
     * Si se elimina un Pato, se encarga de disminuir el ducksCount
     * @param position posicion en la LevelScene
     */
    void deleteObjectAt(const QPointF& position);

    /**
     * Crea un nuevo Object con el tipo y la posicion recibidas por parametro.
     * La posicion es redondeada en caso de ser flotante
     * El objeto es agregado al mapa.
     * @param type tipo del objeto
     * @param pos posicion en la que se quiere crear el objeto
     */
    void addNewObject(ObjectType type, QPointF pos);

    /**
     * Se encarga de añadir el objeto de forma gráfica en el mapa, para eso usa QGraphicsPixmapItem.
     * Si el objeto se quiere agregar en una posicion que esta ocupada, no lo agrega.
     * @param object referencia al objeto que se quiere agregar al mapa
     * @param addInList
     */
    void addObjectInMap(const Object& object, bool addInList);

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    // void toggleAddingObject(ObjectType type);

public:
    LevelScene(QObject* parent, std::vector<Object>& objects);
    ~LevelScene() override = default;

    int getMapWidth() const;
    int getMapHeight() const;

    void selectObjectType(ObjectType type);

    void clearAll();
    // Se encarga de cargar un mapa del tamaño pasado por parametro.
    // Cargara en el mapa los objetos de la lista objects, que ya se tiene la referencia en esta
    // clase.
    void loadMap(int mapWidth, int mapHeight);
    void drawBackground(QPainter* painter, const QRectF& rect) override;
    // void zoom(double factor);
    bool enoughDucks() const;
    bool isEmptyPosition(QRectF itemRect);

signals:
    void addingObjectChanged(ObjectType type);
    void resizeView();
};

#endif  // LEVELSCENE_H
