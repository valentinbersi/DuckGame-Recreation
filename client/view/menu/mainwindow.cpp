#include "mainwindow.h"

#include <QDebug>
#include <QDir>
#include "common_init.h"

#include "ui_mainwindow.h"

void MainWindow::setPagesAndConnections() {
    menu = new mainMenu();
    config= new configurationPage();
    join_game = new joinGame();
    new_game = new newGame();
    match_started = new matchStarted();

    ui->stackedWidget->addWidget(menu);
    ui->stackedWidget->addWidget(config);
    ui->stackedWidget->addWidget(join_game);
    ui->stackedWidget->addWidget(new_game);
    ui->stackedWidget->addWidget(match_started);

    ui->stackedWidget->setCurrentWidget(menu);

    connect(menu, &mainMenu::play, this, &MainWindow::irASeleccionJugadores);
    connect(menu, &mainMenu::exit, this, &MainWindow::salirDelJuego);

    connect(config, &configurationPage::joinGameClicked, this, &MainWindow::joinAMatch);
    connect(config, &configurationPage::newGameClicked, this, &MainWindow::createAMatch);
    connect(config, &configurationPage::backClicked, this, &MainWindow::previousMenu);

    connect(new_game, &newGame::playMatchClicked, this, &MainWindow::startGame);
    connect(new_game, &newGame::backClicked, this, &MainWindow::previousMenu);

    connect(join_game, &joinGame::playMatchClicked, this, &MainWindow::startGame);
    connect(join_game, &joinGame::backClicked, this, &MainWindow::previousMenu);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    common_init(this, ":/backgrounds/duck-game.png"); // ver si va o no

    setPagesAndConnections();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::irASeleccionJugadores() {
    ui->stackedWidget->setCurrentIndex(1); // esto es para ir a la pagina 1 del menu (estaria en la 0)
}

void MainWindow::salirDelJuego() {
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
        //QMessageBox::information(this, "Crear Partida", QString("Partida creada para %1 jugador(es)").arg(cantJugadores));
        ui->stackedWidget->setCurrentIndex(3);
    }
}

// PODRIA UNIR ESTAS DOS FUNCIONES Y LLAMARLAS CON EL INDEX DE PARAMETRO

void MainWindow::joinAMatch() {
    int playersNumbers = config->getSelectedPlayers();
    if (playersNumbers == -1) { // esto creo que aca no deberia estar, sino en config
        QMessageBox::warning(this, "Error", "Seleccioná si vas a jugar con 1 o 2 jugadores antes de continuar");
    }else {
        ui->stackedWidget->setCurrentIndex(2);
    }
}

void MainWindow::previousMenu() {
    int menuActual = ui->stackedWidget->currentIndex();
    if (menuActual == 1)
        ui->stackedWidget->setCurrentIndex(0);
    if (menuActual == 2 || menuActual == 3)
        ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::startGame() {
    //ui->stackedWidget->setCurrentIndex(4);
    emit initMatch();
    close();
}
