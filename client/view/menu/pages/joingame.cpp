#include "joingame.h"

#include <QDebug>
#include <QMessageBox>

joinGame::joinGame(QWidget* parent, GameInfo& gameInfo):
        QWidget(parent), ui(new Ui::joinGame), gameInfo(gameInfo) {
    ui->setupUi(this);

    connect(ui->buttonPlay, &QPushButton::clicked, this, &joinGame::onPlayClicked);
    connect(ui->buttonBack, &QPushButton::clicked, this, &joinGame::backClicked);
}

bool joinGame::verificarDatos() {
    bool matchIDIngresado = !ui->lineEditMatchID->text().isEmpty();
    bool jugador1Ingresado = !ui->lineEditPlayer1->text().isEmpty();

    bool jugador2Ingresado = true;
    if (gameInfo.playersNumber == 2)
        jugador2Ingresado = !ui->lineEditPlayer2->text().isEmpty();

    return (matchIDIngresado && jugador1Ingresado && jugador2Ingresado);
}

void joinGame::onPlayClicked() {
    if (!verificarDatos()) {
        QMessageBox::warning(this, "Datos incompletos",
                             "Por favor, completa todos los datos antes de continuar.");
        return;
    }
    gameInfo.player1Name = ui->lineEditPlayer1->text().toStdString();
    gameInfo.player2Name =
            ui->lineEditPlayer2->text().isEmpty() ? "" : ui->lineEditPlayer2->text().toStdString();
    gameInfo.matchID = ui->lineEditMatchID->text().toUShort();

    emit playMatchClicked();
}

joinGame::~joinGame() { delete ui; }
