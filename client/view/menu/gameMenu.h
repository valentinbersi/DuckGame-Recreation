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
#include "matchSetup.h"
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
    Communicator& communicator;
    bool& twoPlayersLocal;
    GameInfo gameInfo;

    QPointer<mainMenu> menu;
    QPointer<configurationPage> config;
    QPointer<matchSetup> join_game;
    QPointer<matchSetup> new_game;

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
    void showJoinWaitingPage();
};

#endif  // MAINWINDOW_H
