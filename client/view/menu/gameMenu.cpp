#include "gameMenu.h"

#include <QDebug>
#include <QDir>

#include "common_init.h"
#include "ui_gamemenu.h"
#include "waitingPage.h"

#define BACKGROUND_MENU ":/backgrounds/duck-game.png"

GameMenu::GameMenu(QWidget* parent, Communicator& communicator, bool& twoPlayersLocal):
        QMainWindow(parent),
        ui(new Ui::GameMenu),
        communicator(communicator),
        twoPlayersLocal(twoPlayersLocal),
        gameInfo() {
    ui->setupUi(this);

    common_init(this, BACKGROUND_MENU);

    menu = new mainMenu(this);
    config = new configurationPage(this, gameInfo, communicator);

    setPagesAndConnections();
}

void GameMenu::setPagesAndConnections() {
    ui->stackedWidget->addWidget(menu);
    ui->stackedWidget->addWidget(config);

    ui->stackedWidget->setCurrentWidget(menu);

    connect(menu, &mainMenu::play, this, [this]() { changePage(config); });
    connect(menu, &mainMenu::exitGameRequested, this, &QApplication::quit);

    connect(config, &configurationPage::playMatchClicked, this, &GameMenu::showWaitingPage);
    connect(config, &configurationPage::backClicked, this, [this]() { changePage(menu); });
}

GameMenu::~GameMenu() { delete ui; }

void GameMenu::changePage(QWidget* page) { ui->stackedWidget->setCurrentWidget(page); }

void GameMenu::showWaitingPage() {
    WaitingPage* waitingPage;
    if (gameInfo.matchID == 0)
        waitingPage = new WaitingPage(this, true, communicator, gameInfo);
    else
        waitingPage = new WaitingPage(this, false, communicator, gameInfo);
    ui->stackedWidget->addWidget(waitingPage);
    changePage(waitingPage);
    QApplication::processEvents();
    connect(waitingPage, &WaitingPage::startMatch, this, &GameMenu::startGameHandler);
}

//void GameMenu::showWaitingPage() {
//    auto* host_waiting_page = new WaitingPage(this, true, communicator, gameInfo);
//    ui->stackedWidget->addWidget(host_waiting_page);
//    changePage(host_waiting_page);
//
//    connect(host_waiting_page, &WaitingPage::startMatch, this, &GameMenu::startGameHandler);
//}
//
//void GameMenu::showJoinWaitingPage() {
//    auto* join_waiting_page = new WaitingPage(this, false, communicator, gameInfo);
//    ui->stackedWidget->addWidget(join_waiting_page);
//    changePage(join_waiting_page);
//    QApplication::processEvents();
//    connect(join_waiting_page, &WaitingPage::startMatch, this, &GameMenu::startGameHandler);
//}

void GameMenu::startGameHandler() {
    twoPlayersLocal = (gameInfo.playersNumber == 2);
    emit startGame();
    close();
    QCoreApplication::exit(0);
}
