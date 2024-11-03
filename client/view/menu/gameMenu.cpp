#include "gameMenu.h"

#include <QDebug>
#include <QDir>
#include <QPushButton>

#include "common_init.h"
#include "ui_gamemenu.h"

GameMenu::GameMenu(QWidget* parent, Communicator& communicator)
        : QMainWindow(parent),
        ui(new Ui::GameMenu),
        communicator(communicator),
        gameInfo() {
    ui->setupUi(this);

    common_init(this, ":/backgrounds/duck-game.png");

    menu = new mainMenu(this);
    config = new configurationPage(this, gameInfo);
    join_game = new joinGame(this, gameInfo);
    new_game = new newGame(this, gameInfo);

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

    connect(new_game, &newGame::playMatchClicked, this, &GameMenu::startGameHandler);
    connect(new_game, &newGame::backClicked, this, [this]() { changePage(config); });

    connect(join_game, &joinGame::playMatchClicked, this, &GameMenu::startGameHandler);
    connect(join_game, &joinGame::backClicked, this, [this]() { changePage(config); });
}

GameMenu::~GameMenu() {
    delete ui;
}

void GameMenu::changePage(QWidget* page) {
    ui->stackedWidget->setCurrentWidget(page);
}

void GameMenu::startGameHandler() {
    sendMessageToServer();
    emit startGame();
    close();
    QCoreApplication::exit(0); // esto es necesario??
}

void GameMenu::sendMessageToServer() {
    // mensajes en consola para chequear que los datos se guardaron bien.
    qDebug() << "Game Info:";
    qDebug() << "Players Numbers:" << gameInfo.playersNumber;
    qDebug() << "Player 1 Name:" << QString::fromStdString(gameInfo.player1Name);
    qDebug() << "Player 2 Name:" << QString::fromStdString(gameInfo.player2Name);
    qDebug() << "Match ID:" << gameInfo.matchID;
    qDebug() << "Map Name:" << QString::fromStdString(gameInfo.selectedMap);

    // si se crea partida tendria que mostrar por pantalla el matchID.

    LobbyRequest request = gameInfo.isNewGame ? LobbyRequest::NEWMATCH : LobbyRequest::JOINMATCH;

    auto message = std::make_unique<LobbyMessage>(
            request,
            gameInfo.playersNumber,
            gameInfo.player1Name,
            gameInfo.player2Name,
            gameInfo.matchID
    );

//    if (!communicator.trysend(std::move(message))) {
//        qDebug() << "Error al enviar el mensaje.";
//    }

    // mensajes en consola para chequear que los datos se guardaron bien en el LobbyMessage.
    qDebug() << "Lobby Message Info:";
    qDebug() << "Request:" << message->request;
    qDebug() << "Players Numbers:" << message->playerCount;
    qDebug() << "Player 1 Name:" << QString::fromStdString(message->player1Name);
    qDebug() << "Player 2 Name:" << QString::fromStdString(message->player2Name);
    qDebug() << "Match ID:" << message->matchId;
    //qDebug() << "Map Name:" << QString::fromStdString(gameInfo.selectedMap);
}