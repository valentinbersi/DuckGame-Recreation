#include "mainwindow.h"

#include <QDebug>
#include <QDir>

#include "common_init.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent, Communicator& communicator)
        : QMainWindow(parent),
        ui(new Ui::MainWindow),
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

void MainWindow::setPagesAndConnections() {
    ui->stackedWidget->addWidget(menu);
    ui->stackedWidget->addWidget(config);
    ui->stackedWidget->addWidget(join_game);
    ui->stackedWidget->addWidget(new_game);

    ui->stackedWidget->setCurrentWidget(menu);

    connect(menu, &mainMenu::play, this, [this]() { changePage(config); });
    connect(menu, &mainMenu::exit, this, &MainWindow::exitTheGame);

    connect(config, &configurationPage::joinGameClicked, this, &MainWindow::joinAMatch);
    connect(config, &configurationPage::newGameClicked, this, &MainWindow::createAMatch);
    connect(config, &configurationPage::backClicked, this, [this]() { changePage(menu); });

    connect(new_game, &newGame::playMatchClicked, this, &MainWindow::startGameHandler);
    connect(new_game, &newGame::backClicked, this, [this]() { changePage(config); });

    connect(join_game, &joinGame::playMatchClicked, this, &MainWindow::startGameHandler);
    connect(join_game, &joinGame::backClicked, this, [this]() { changePage(config); });
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::changePage(QWidget* page) {
    ui->stackedWidget->setCurrentWidget(page);
}

void MainWindow::exitTheGame() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Salir", "¿Seguro que querés salir?", QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void MainWindow::createAMatch() {
    int playersNumbers = config->getSelectedPlayers();
    if (playersNumbers == -1) { // esto creo que aca no deberia estar, sino en config
        QMessageBox::warning(this, "Error", "Seleccioná si vas a jugar con 1 o 2 jugadores antes de continuar");
    } else {
        changePage(new_game);
    }
}

void MainWindow::joinAMatch() {
    int playersNumbers = config->getSelectedPlayers();
    if (playersNumbers == -1) { // esto creo que aca no deberia estar, sino en config
        QMessageBox::warning(this, "Error", "Seleccioná si vas a jugar con 1 o 2 jugadores antes de continuar");
    } else {
        changePage(join_game);
    }
}

void MainWindow::startGameHandler() {
    sendMessageToServer();
    emit startGame();
    close();
    QCoreApplication::exit(0);
}

void MainWindow::sendMessageToServer() {
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

    qDebug() << "Lobby Message Info:";
    qDebug() << "Request:" << message->request;
    qDebug() << "Players Numbers:" << message->playerCount;
    qDebug() << "Player 1 Name:" << QString::fromStdString(message->player1Name);
    qDebug() << "Player 2 Name:" << QString::fromStdString(message->player2Name);
    qDebug() << "Match ID:" << message->matchId;
    //qDebug() << "Map Name:" << QString::fromStdString(gameInfo.selectedMap);
}