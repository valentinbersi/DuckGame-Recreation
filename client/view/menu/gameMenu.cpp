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
    waitingPage = nullptr;

    setPagesAndConnections();
}

void GameMenu::setPagesAndConnections() {
    ui->stackedWidget->addWidget(menu);
    ui->stackedWidget->addWidget(config);

    ui->stackedWidget->setCurrentWidget(menu);

    connect(menu, &mainMenu::play, this, [this]() { changePage(config); });
    connect(menu, &mainMenu::exitGameRequested, this, &GameMenu::closeMenu);

    connect(config, &configurationPage::playMatchClicked, this, &GameMenu::showWaitingPage);
    connect(config, &configurationPage::backClicked, this, [this]() { changePage(menu); });
}

GameMenu::~GameMenu() {
    delete ui;
    delete menu;
    delete config;
    delete waitingPage;
}

void GameMenu::changePage(QWidget* page) { ui->stackedWidget->setCurrentWidget(page); }

void GameMenu::showWaitingPage() {
    if (gameInfo.isNewGame)
        waitingPage = new WaitingPage(this, communicator, gameInfo);
    else
        waitingPage = new WaitingPage(this, communicator, gameInfo);
    ui->stackedWidget->addWidget(waitingPage);
    changePage(waitingPage);
    QApplication::processEvents();
    connect(waitingPage, &WaitingPage::startMatch, this, &GameMenu::startGameHandler);
}

void GameMenu::startGameHandler() {
    twoPlayersLocal = (gameInfo.playersNumber == 2);
    emit startGame();
    closeMenu();
}

void GameMenu::closeMenu() {
    close();
    QApplication::quit();
}
