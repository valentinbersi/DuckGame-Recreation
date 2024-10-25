#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);


    QPixmap pixmap(":/backgrounds/duck-game.png");
    if (pixmap.isNull()) {
        qWarning() << "Failed to load background image.";
        return; // Salir si la imagen no se carga
    }
    QSize windowSize = this->size();
    QPixmap scaledPixmap = pixmap.scaled(windowSize, Qt::KeepAspectRatioByExpanding);
    QPalette palette;
    palette.setBrush(QPalette::Window, scaledPixmap);
    this->setPalette(palette);


    // conecto los botones con las funciones que deben realizar
    connect(ui->btnJugar, &QPushButton::clicked, this, &MainWindow::irASeleccionJugadores);
    connect(ui->btnExit, &QPushButton::clicked, this, &MainWindow::salirDelJuego);

    grupoJugadores = new QButtonGroup(this);
    grupoJugadores->addButton(ui->radio1Jugador, 1);
    grupoJugadores->addButton(ui->radio2Jugador, 2);

    connect(ui->btnUnirse, &QPushButton::clicked, this, &MainWindow::unirseAPartida);
    connect(ui->btnCrear, &QPushButton::clicked, this, &MainWindow::crearPartida);
    connect(ui->btnVolver, &QPushButton::clicked, this, &MainWindow::menuAnterior);

    connect(ui->btnJugar_2, &QPushButton::clicked, this, &MainWindow::iniciarPartida);
    connect(ui->btnVolver_2, &QPushButton::clicked, this, &MainWindow::menuAnterior);
    //connect(ui->mapsList, &QPushButton::clicked, this, &MainWindow::menuAnterior);


    connect(ui->btnJugar_3, &QPushButton::clicked, this, &MainWindow::iniciarPartida);
    connect(ui->btnVolver_3, &QPushButton::clicked, this, &MainWindow::menuAnterior);
    //connect(ui->partidasList, &QPushButton::clicked, this, &MainWindow::menuAnterior);
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

void MainWindow::crearPartida() {
    // Aca va la lógica para crear a una partida
    int cantJugadores = grupoJugadores->checkedId(); // 1 o 2
    if (cantJugadores == -1) {
        QMessageBox::warning(this, "Error", "Seleccioná si vas a jugar con 1 o 2 jugadores antes de continuar");
    } else {
        //QMessageBox::information(this, "Crear Partida", QString("Partida creada para %1 jugador(es)").arg(cantJugadores));
        ui->stackedWidget->setCurrentIndex(3);
    }
}


void MainWindow::unirseAPartida() {
    // Aca va la lógica para unirse a una partida
    int cantJugadores = grupoJugadores->checkedId(); // 1 o 2
    if (cantJugadores == -1) {
        QMessageBox::warning(this, "Error", "Seleccioná si vas a jugar con 1 o 2 jugadores antes de continuar");
    }else {
        //QMessageBox::information(this, "Unirse a Partida", QString("Partida iniciada para %1 jugador(es)").arg(cantJugadores));
        ui->stackedWidget->setCurrentIndex(2);
    }
}

void MainWindow::menuAnterior() {
    int menuActual = ui->stackedWidget->currentIndex();
    if (menuActual == 1)
        ui->stackedWidget->setCurrentIndex(0);
    if (menuActual == 2 || menuActual == 3)
        ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::iniciarPartida() {
    QWidget *widget = ui->stackedWidget->widget(4);
    widget->setObjectName("page4");
    widget->setStyleSheet("#page4 { background-image: url(:/backgrounds/partida-run.png); background-position: center; background-repeat: no-repeat; }");
    ui->stackedWidget->setCurrentIndex(4);
}

