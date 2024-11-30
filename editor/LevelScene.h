#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <list>

#include "Object.h"


class LevelScene: public QGraphicsScene {
    Q_OBJECT

private:
    int gridWidth;              /** ancho de la grilla (no del mapa) */
    int gridHeight;             /** alto de la grilla (no del mapa) */
    std::list<Object>& objects; /** referencia a la lista de objetos del editor */
    QMap<QGraphicsPixmapItem*, Object*>
            objectsMap; /** map usado para asociar el item gráfico de Qt con el Object en memoria*/

    QGraphicsPixmapItem* selectedItem; /** apunta al item seleccionado que quiere moverse*/
    QPointF originalItemPos;           /** posicion original del item que esta siendo seleccionado*/

    int ducksCount;             /** cantidad de spawn de patos en el mapa */
    ObjectType objectTypeToAdd; /** tipo de objeto seleccionado para agregar */

    /** flags que indican si se esta queriendo agregar o eliminar un objeto del mapa*/
    bool isAddingObject = false;
    bool isDeletingObject = false;

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
     * Se encarga tambien de resizear el mapa si se agrega el objeto por fuera del mismo.
     * @param type tipo del objeto
     * @param pos posicion en la que se quiere crear el objeto
     */
    void addNewObject(ObjectType type, QPointF pos);

    /**
     * Se encarga de añadir el objeto de forma gráfica en el mapa, para eso usa QGraphicsPixmapItem.
     * Si el objeto se quiere agregar en una posicion que esta ocupada, no lo agrega.
     * @param object referencia al objeto que se quiere agregar al mapa
     * @param addInList indica si el objeto debe agregarse o no la lista objects
     */
    void insertObjectInMap(Object& object, bool addInList);

    /**
     * Itera sobre la lista de items y compara el itemRect
     * con los rectangulos que ocupan todos los vertices, chequeando si se intersecan o no.
     * @param itemRect rectangulo gráfico que ocuparia el item
     * @return si la posición es válida para agregar el item
     */
    bool isEmptyPosition(QRectF itemRect);

    /**
     * Evento cuando se presiona el mouse.
     * Hay 3 opciones:
     *  1) si se presiona el boton derecho sobre un elemento/objeto, lo elimina
     *  2) si se tiene seleccionado algun objeto, se agrega en el mapa donde se presiona.
     *  3) si se presiona sobre un item, este es seleccionado para moverlo (debera mantener apretado
     * el click izquierdo)
     * @param event evento del mouse de QT
     */
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

    /**
     * Si se tiene un objeto seleccionado, lo mueve junto con el cursor.
     * @param event evento del mouse de QT
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;

    /**
     * Evento cuando se suelta el click izquierdo del mouse.
     * Si se tiene un objeto seleccionado, este sera posicionado donde se suelta el mouse.
     * En caso de que la posicion este ocupada, el objeto volvera a su posicion original.
     * @param event evento del mouse de QT
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;


public:
    LevelScene(QObject* parent, std::list<Object>& objects);
    ~LevelScene() override = default;

    /**
     * @return ancho del mapa (gridWidth / PIXEL_SIZE)
     */
    [[nodiscard]] int getMapWidth() const;
    /**
     * @return alto del mapa (gridHeight / PIXEL_SIZE)
     */
    [[nodiscard]] int getMapHeight() const;

    /**
     * Setea el tipo de objeto seleccionado para agregar al mapa.
     * Una vez seteado el tipo, se puede presionar en el mapa para agregar un objeto de ese tipo
     * Si el tipo recibido es el que actualmente esta seleccionado, se deselecciona,
     * dando asi la opcion de seleccionar y deseleccionar el objeto
     * Emite la signal addingObjectChanged
     * @param type tipo del objeto que se quiere agregar
     */
    void selectObjectType(ObjectType type);

    /**
     * Limpia todos los elementos gráficos, reinicia el objectsMap y vacia la lista objects.
     */
    void clearAll();

    /**
     * Se encarga de cargar un mapa del tamaño pasado por parametro.
     * Cargara en el mapa los objetos de la lista objects, que ya se tiene la referencia en esta
     * clase.
     * @param mapWidth ancho del mapa
     * @param mapHeight alto del mapa
     * ambos parametros se multiplicaran por el PIXEL_SIZE para obtener el tamaño de la grilla.
     */
    void loadMap(int mapWidth, int mapHeight);

    /**
     * dibuja la grilla.
     * @param painter
     * @param rect
     */
    void drawBackground(QPainter* painter, const QRectF& rect) override;

    /**
     * @return si la cantidad de patos es o no suficiente para iniciar el juego.
     */
    [[nodiscard]] bool enoughDucks() const;

signals:
    void addingObjectChanged(ObjectType type);
    void resizeView();
    void requestDragModeChange(QGraphicsView::DragMode);
};
