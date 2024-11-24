#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <map>
#include <string>
#include <vector>

#include "levelscene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow* ui;
    std::string background;
    std::vector<Object> objects;
    LevelScene* scene;
    std::map<QAction*, ObjectType> actionTypeMap;

    // void wheelEvent(QWheelEvent* event) override;
    /**
     * Handler que captura el evento de push del boton NewMap.
     * Se encarga de iniciar un nuevo mapa.
     * Emitira un mensaje emergente el cual consultara al usuario si esta seguro de crear un mapa
     * nuevo y si lo quiere guardar al que esta. Una vez creado el nuevo mapa, mostrara un mensaje
     * de exito.
     */
    void on_actionNewMap_triggered();

    /**
     * Handler que captura el evento de push del boton EditMap.
     * Se encarga de cargar un mapa ya creado.
     * Emitira un mensaje emergente el cual consultara al usuario si esta seguro de cargar un mapa
     * y si lo quiere guardar al que esta.
     * Si se quiere cargar un mapa, se abrira la carpeta maps/ donde estan cargados los mapas del
     * juego y el usuario debera elegir que mapa quiere. Si elige un mapa valido, se cargara el
     * mapa. Una vez cargado el nuevo mapa, mostrara un mensaje de exito. O emitira un mensaje de
     * error.
     */
    void on_actionEditMap_triggered();

    /**
     * Setea los botones de accion de la barra de opciones.
     * Setea el actionTypeMap, asociando cada boton con el tipo de objeto correspondiente.
     * Cuando los botones se apreten, se podran agregar los objetos al mapa.
     * Tambien se encarga de que se deseleccionen cuando asi lo requiera.
     */
    void setActionButtons();

    /**
     * Resizea la escena basandose en el tamaño del mapa, con el fin de poder agrandar el mapa si el
     * usuario asi lo desea.
     */
    void onSceneResize();
};
#endif  // MAINWINDOW_H
