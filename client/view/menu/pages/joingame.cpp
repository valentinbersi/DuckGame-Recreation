#include "joingame.h"
#include <QMessageBox>

joinGame::joinGame(QWidget* parent): QWidget(parent), ui(new Ui::joinGame) {
    ui->setupUi(this);

    connect(ui->buttonPlay, &QPushButton::clicked, this, &joinGame::playMatchClicked);
    connect(ui->buttonBack, &QPushButton::clicked, this, &joinGame::backClicked);

    connect(ui->lineEditPlayer1, &QLineEdit::textChanged, this, &joinGame::verificarDatos);
    connect(ui->lineEditPlayer2, &QLineEdit::textChanged, this, &joinGame::verificarDatos);
    connect(ui->lineEditMatchID, &QLineEdit::textChanged, this, &joinGame::verificarDatos);


    ui->buttonPlay->setEnabled(false);
}

joinGame::~joinGame() { delete ui; }

void joinGame::verificarDatos() {
    bool matchIDIngresado = !ui->lineEditMatchID->text().isEmpty();

    bool jugador1Ingresado = !ui->lineEditPlayer1->text().isEmpty();

//    bool jugador2Ingresado = true; // Asumimos juego de un jugador por defecto
//    if (esModoDosJugadores) {
//        jugador2Ingresado = !ui->lineEditPlayer2->text().isEmpty();
//    }

    bool jugador2Ingresado = !ui->lineEditPlayer2->text().isEmpty();


    ui->buttonPlay->setEnabled(matchIDIngresado && jugador1Ingresado && jugador2Ingresado);
}