#include "gameMenu.h"

#include <QDebug>
#include <QDir>
#include <QPushButton>

#include "common_init.h"
#include "ui_gamemenu.h"
#include "hostwaitingpage.h"

GameMenu::GameMenu(QWidget* parent, Communicator& communicator, bool& twoPlayersLocal)
        : QMainWindow(parent),
        ui(new Ui::GameMenu),
        communicator(communicator),
        twoPlayersLocal(twoPlayersLocal),
        gameInfo() {
    ui->setupUi(this);

    common_init(this, ":/backgrounds/duck-game.png");

    menu = new mainMenu(this);
    config = new configurationPage(this, gameInfo);
    join_game = new joinGame(this, communicator, gameInfo);
    new_game = new newGame(this, communicator, gameInfo);

    setPagesAndConnections();
}

void GameMenu::setPagesAndConnections() {
    ui->stackedWidget->addWidget(menu);
    ui->stackedWidget->addWidget(config);
    ui->stackedWidget->addWidget(join_game);
    ui->stackedWidget->addWidget(new_game);

    ui->stackedWidget->setCurrentWidget(menu);

    connect(menu, &mainMenu::play, this, [this]() { changePage(config); });
    connect(menu, &mainMenu::exitGameRequested, this, &QApplication::quit);

    connect(config, &configurationPage::joinGameClicked, this, [this]() { changePage(join_game); });
    connect(config, &configurationPage::newGameClicked, this, [this]() { changePage(new_game); });
    connect(config, &configurationPage::backClicked, this, [this]() { changePage(menu); });

    connect(new_game, &newGame::playMatchClicked, this, &GameMenu::showHostWaitingPage);
    connect(new_game, &newGame::backClicked, this, [this]() { changePage(config); });

    connect(join_game, &joinGame::playMatchClicked, this, &GameMenu::showJoinWaitingPage);
    connect(join_game, &joinGame::backClicked, this, [this]() { changePage(config); });
}

GameMenu::~GameMenu() {
    delete ui;
}

void GameMenu::changePage(QWidget* page) {
    ui->stackedWidget->setCurrentWidget(page);
}

void GameMenu::showHostWaitingPage() {
    qDebug() << "showHostWaitingPage";
    qDebug() << "Match ID:" << gameInfo.matchID;
    auto* host_waiting_page = new hostWaitingPage(this, communicator, gameInfo);
    ui->stackedWidget->addWidget(host_waiting_page);
    changePage(host_waiting_page);

    connect(host_waiting_page, &hostWaitingPage::startMatch, this, &GameMenu::startGameHandler);
}

void GameMenu::showJoinWaitingPage() {
    auto* join_waiting_page = new joinWaitingPage(this, communicator);
    ui->stackedWidget->addWidget(join_waiting_page);
    changePage(join_waiting_page);

    connect(join_waiting_page, &joinWaitingPage::matchStarted, this, &GameMenu::startGameHandler);
    join_waiting_page->waitForMatchStart();
}

void GameMenu::startGameHandler() {
    if (gameInfo.playersNumber == 2)
        twoPlayersLocal = true;
    emit startGame();
    close();
    QCoreApplication::exit(0); // esto es necesario??
}