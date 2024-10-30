#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QButtonGroup>
#include <QMainWindow>
#include <QMessageBox>
#include <QPointer>

#include "pages/configurationpage.h"
#include "pages/joingame.h"
#include "pages/mainmenu.h"
#include "pages/matchstarted.h"
#include "pages/newgame.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow {
    Q_OBJECT


private:
    Ui::MainWindow* ui;

    QPointer<mainMenu> menu;
    QPointer<configurationPage> config;
    QPointer<joinGame> join_game;
    QPointer<newGame> new_game;
    QPointer<matchStarted> match_started;

    void setPagesAndConnections();
    void irASeleccionJugadores();
    void salirDelJuego();
    void createAMatch();
    void joinAMatch();
    void previousMenu();
    void startGame();

signals:
    void initMatch();


public:
    MainWindow(QWidget* parent);
    ~MainWindow() override;
};

#endif  // MAINWINDOW_H
