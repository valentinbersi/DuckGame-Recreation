#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QButtonGroup>
#include <QMainWindow>
#include <QMessageBox>

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
    QButtonGroup* grupoJugadores;

    mainMenu *menu;
    configurationPage *config;
    joinGame *join_game;
    newGame *new_game;
    matchStarted *match_started;

    void irASeleccionJugadores();
    void salirDelJuego();
    void createAMatch();
    void joinAMatch();
    void previousMenu();
    void startGame();

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
};

#endif  // MAINWINDOW_H
