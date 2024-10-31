#include "mainwindow.h"

#include <QDebug>
#include <QDir>

#include "common_init.h"
#include "ui_mainwindow.h"

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

MainWindow::MainWindow(QWidget* parent)
        : QMainWindow(parent),
        ui(new Ui::MainWindow),
        message() {
    ui->setupUi(this);

    common_init(this, ":/backgrounds/duck-game.png");

    menu = new mainMenu(this);
    config = new configurationPage(this, message);
    join_game = new joinGame(this, message);
    new_game = new newGame(this, message);

    setPagesAndConnections();
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
    qDebug() << "Lobby Message Info:";
    qDebug() << "Players Count:" << message.getPlayerCount();
    qDebug() << "Player 1 Name:" << QString::fromStdString(message.getPlayer1Name());
    qDebug() << "Player 2 Name:" << QString::fromStdString(message.getPlayer2Name());
    qDebug() << "Match ID:" << message.getMatchId();
    qDebug() << "Map Name:" << QString::fromStdString(message.getMapChosen());
    emit startGame();
    close();
    QCoreApplication::exit(0);
}