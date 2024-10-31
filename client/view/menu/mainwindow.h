#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QButtonGroup>
#include <QMainWindow>
#include <QMessageBox>
#include <QPointer>

#include "GameInfo.h"
#include "MyLobbyMessage.h"
#include "configurationpage.h"
#include "joingame.h"
#include "mainmenu.h"
#include "newgame.h"

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

    LobbyMessage_ message;

    void setPagesAndConnections();
    void exitTheGame();
    void createAMatch();
    void joinAMatch();
    void startGameHandler();
    void changePage(QWidget* page);

signals:
    void startGame();

public:
    explicit MainWindow(QWidget* parent);
    ~MainWindow() override;
};

#endif  // MAINWINDOW_H
