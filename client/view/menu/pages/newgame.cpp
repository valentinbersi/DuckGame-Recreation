#include "newgame.h"

#include <QStringListModel>

newGame::newGame(QWidget* parent): QWidget(parent), ui(new Ui::newGame) {
    ui->setupUi(this);

    // inicializo la lista de mapas en modo de prueba.
    QStringList mapas = {"Selva", "Bosque", "Nave Espacial"};
    auto *modeloMapas = new QStringListModel(mapas, this);
    ui->mapsList->setModel(modeloMapas);

    connect(ui->buttonPlay, &QPushButton::clicked, this, &newGame::playMatchClicked);
    connect(ui->buttonBack, &QPushButton::clicked, this, &newGame::backClicked);

    connect(ui->lineEditPlayer1, &QLineEdit::textChanged, this, &newGame::verificarDatos);
    connect(ui->lineEditPlayer2, &QLineEdit::textChanged, this, &newGame::verificarDatos);
    connect(ui->mapsList->selectionModel(), &QItemSelectionModel::selectionChanged, this, &newGame::verificarDatos);

    ui->buttonPlay->setEnabled(false);
}

void newGame::verificarDatos() {
    bool mapaSeleccionado = !ui->mapsList->selectionModel()->selectedIndexes().isEmpty();

    bool jugador1Ingresado = !ui->lineEditPlayer1->text().isEmpty();

    //    bool jugador2Ingresado = true; // Asumimos juego de un jugador por defecto
    //    if (esModoDosJugadores) {
    //        jugador2Ingresado = !ui->lineEditPlayer2->text().isEmpty();
    //    }

    bool jugador2Ingresado = !ui->lineEditPlayer2->text().isEmpty();

    ui->buttonPlay->setEnabled(mapaSeleccionado && jugador1Ingresado && jugador2Ingresado);
}

newGame::~newGame() { delete ui; }
