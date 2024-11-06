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
#include "hostwaitingpage.h"
#include "joingame.h"
#include "joinwaitingpage.h"
#include "mainmenu.h"
#include "newgame.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class GameMenu;
}
QT_END_NAMESPACE

class GameMenu: public QMainWindow {
    Q_OBJECT


private:
    Ui::GameMenu* ui;
    Communicator& communicator;
    bool& twoPlayersLocal;
    GameInfo gameInfo;

    QPointer<mainMenu> menu;
    QPointer<configurationPage> config;
    QPointer<joinGame> join_game;
    QPointer<newGame> new_game;

    void setPagesAndConnections();
    void startGameHandler();
    void changePage(QWidget* page);
    // void sendMessageToServer();
    void showHostWaitingPage();
    // void showJoinWaitingPage();

signals:
    void startGame();

public:
    GameMenu(QWidget* parent, Communicator& communicator, bool& twoPlayersLocal);
    ~GameMenu() override;
};

#endif  // MAINWINDOW_H
