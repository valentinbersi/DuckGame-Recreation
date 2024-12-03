#pragma once

#include <QListWidgetItem>
#include <QMainWindow>
#include <QPushButton>
#include <list>
#include <map>
#include <string>

#include "LevelScene.h"
#include "MapData.h"
#include "MapManager.h"
#include "Types.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ViewController;
}
QT_END_NAMESPACE

class ViewController: public QMainWindow {
    Q_OBJECT

public:
    explicit ViewController(QWidget* parent = nullptr);

    void showStartupInfo();

    ~ViewController() override;

private:
    Ui::ViewController* ui;
    MapData mapData;
    MapManager mapManager;
    LevelScene* scene;

    QPushButton* platformButton;
    QPushButton* spawnDuckButton;
    QPushButton* spawnArmamentButton;
    QPushButton* boxButton;
    std::map<QPushButton*, ObjectType> buttonTypeMap;

    QBrush backgroundBrush;

    /**
     * Carga los backgrounds en la lista de backgrounds.
     * Deja la lista de backgrounds lista para utilizarse.
     */
    void loadBackgrounds();

    /**
    * Handlea la seleccion de algun elemento del mapa en la lista,
    * llama a changeBackgroundBrush para que setee el background seleccionado.
    */
    void onBackgroundSelected(const QListWidgetItem* item);

    /**
     * Toma el background seleccionado y lo setea como fondo del mapa
     */
    void changeBackgroundBrush();

    /**
     * Configura los botones de la ToolBar, con sus icones correspondientes.
     * Asocia los botones a los tipos de objetos que representan.
     * Conecta los botones con los metodos necesarios para darles la funcionalidad de agregar el objeto en el mapa
     */
    void setupToolBar();

    /**
     * Handler que captura el evento de push del boton NewMap.
     * Se encarga de iniciar un nuevo mapa.
     * Emitira un mensaje emergente el cual consultara al usuario si esta seguro de crear un mapa
     * nuevo y si lo quiere guardar al que esta. Una vez creado el nuevo mapa, mostrara un mensaje
     * de exito.
     */
    void on_actionNewMap_triggered();

    /**
    * Handler que captura el evento de push del boton SaveMap.
    * Se encarga de permitirle al usuario guardar el mapa.
    * Abre la carpeta de archivos para que el usuario elija donde guardar el mapa.
    * Se mostrara un mensaje informando si el mapa fue o no guardado.
    */
    void on_actionSaveMap_triggered();


    /**
     * Handler que captura el evento de push del boton EditMap.
     * Se encarga de cargar un mapa ya creado.
     * Emitira un mensaje emergente el cual consultara al usuario si esta seguro de cargar un mapa
     * y si lo quiere guardar al que esta.
     * Si se quiere cargar un mapa, se abrira la carpeta de archivos, donde el usuario debe elegir el archivo del mapa que desea cargar.
     * Si elige un mapa valido, se cargara el mapa. Una vez cargado el nuevo mapa, mostrara un mensaje de exito. O emitira un mensaje de error.
     */
    void on_actionEditMap_triggered();

    // /**
    //  * Setea los botones de accion de la barra de opciones.
    //  * Setea el actionTypeMap, asociando cada boton con el tipo de objeto correspondiente.
    //  * Cuando los botones se apreten, se podran agregar los objetos al mapa.
    //  * Tambien se encarga de que se deseleccionen cuando asi lo requiera.
    //  */
    // void setActionButtons();

    /**
     * Resizea la escena basandose en el tamaño del mapa, con el fin de poder agrandar el mapa si el
     * usuario asi lo desea.
     */
    void onSceneResize();

    /**
     * Genera un mensaje emergente, preguntandole al usuario si quiere guardar el mapa actual antes
     * de cerrarlo. El usuario tiene 3 opciones: Cancelar la acción, No guardar o Guardar.
     * @return false si se cancela la accion y true si no se cancela.
     * En caso de querer guardar, el mapa se exporta mediante MapManager.
     */
    bool confirmAndSaveMap();

    /**
     * Dibuja el fondo del mapa y el ui
     * @param event evento de Paint de Qt, no es utilizado en este caso
     */
    void paintEvent(QPaintEvent* event) override;

};
