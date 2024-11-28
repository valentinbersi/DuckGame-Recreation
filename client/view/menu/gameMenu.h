#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QButtonGroup>
#include <QMainWindow>
#include <QMessageBox>
#include <QPointer>

#include "Communicator.h"
#include "GameInfo.h"
#include "LobbyMessage.h"
#include "configurationpage.h"
#include "mainmenu.h"
#include "waitingPage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class GameMenu;
}
QT_END_NAMESPACE

class GameMenu: public QMainWindow {
    Q_OBJECT

private:
    Ui::GameMenu* ui;
    Communicator&
            communicator;  /** Referencia al comunicador, para comunicar el lobby con el server */
    bool& twoPlayersLocal; /** booleano del Launcher, para que sepa cuantos jugadores hay*/
    GameInfo gameInfo;     /** Struct que guarda informacion importante para el juego */

    /** Punteros a las paginas usadas en el lobby */
    QPointer<mainMenu> menu;
    QPointer<configurationPage> config;
    QPointer<WaitingPage> waitingPage;

    /**
     * Setea los widgets de las paginas y conecta los botones y las acciones para configurar la
     * funcionalidad del lobby.
     */
    void setPagesAndConnections();

    /**
     * Handler de la señal para iniciar el juego.
     * Se encarga de setear el bool twoPlayersLocal
     * y emitir la señal de que el juego ya empezo para notificar al Launcher
     */
    void startGameHandler();

    /**
     * Cambia a la pagina page
     * @param page pagina a la que quiere cambiar
     */
    void changePage(QWidget* page);

    /**
     * Se encarga de inicializar las pantallas de carga, ya sea la del host o la del join.
     */
    void showWaitingPage();

    void closeEvent(QCloseEvent* event) override;
    void exitGame();

signals:
    void startGame();

public:
    GameMenu(QWidget* parent, Communicator& communicator, bool& twoPlayersLocal);
    ~GameMenu() override;
};

#endif  // MAINWINDOW_H
