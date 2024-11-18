#include "matchSetup.h"

#include <QDebug>
#include <QMessageBox>

#include "ReplyMessage.h"

matchSetup::matchSetup(QWidget* parent, MatchMode matchMode, Communicator& communicator, GameInfo& gameInfo):
        QWidget(parent),
        ui(new Ui::matchSetup),
        matchMode(matchMode),
        communicator(communicator),
        gameInfo(gameInfo) {
    ui->setupUi(this);

    if (matchMode == newMatch) {
        ui->matchIDLabel->setVisible(false);
        ui->lineEditMatchID->setVisible(false);
    }

    connect(ui->buttonPlay, &QPushButton::clicked, this, &matchSetup::onPlayClicked);
    connect(ui->buttonBack, &QPushButton::clicked, this, &matchSetup::backClicked);
}

bool matchSetup::verificarDatos() {
    bool jugador1Ingresado = !ui->lineEditPlayer1->text().isEmpty();
    bool jugador2Ingresado = true;
    if (gameInfo.playersNumber == 2)
        jugador2Ingresado = !ui->lineEditPlayer2->text().isEmpty();

    if (matchMode == joinMatch) {
        bool matchIDIngresado = !ui->lineEditMatchID->text().isEmpty();
        return (matchIDIngresado && jugador1Ingresado && jugador2Ingresado);
    }

    return jugador1Ingresado && jugador2Ingresado;
}

void matchSetup::onPlayClicked() {
    if (!verificarDatos()) {
        QMessageBox::warning(this, "Datos incompletos",
                             "Por favor, completa todos los datos antes de continuar.");
        return;
    }
    gameInfo.player1Name = ui->lineEditPlayer1->text().toStdString();
    gameInfo.player2Name = ui->lineEditPlayer2->text().isEmpty() ? " " : ui->lineEditPlayer2->text().toStdString();

    if (matchMode == joinMatch) {
        gameInfo.matchID = ui->lineEditMatchID->text().toUShort();
    }

    if (initMatchRequest()) {
        emit playMatchClicked();
    }
}

bool matchSetup::initMatchRequest() {
    LobbyRequest requestType = (matchMode == newMatch) ? LobbyRequest::NEWMATCH : LobbyRequest::JOINMATCH;
    auto message = std::make_unique<LobbyMessage>(requestType, gameInfo.playersNumber,
                                                  gameInfo.player1Name, gameInfo.player2Name,
                                                  gameInfo.matchID
    );

    if (communicator.trysend(std::move(message))) {
        // chequear si se envio
        ReplyMessage replyMessage = communicator.blockingRecv();
        // chequear si se recibio bien
        gameInfo.matchID = replyMessage.matchID;
        return true;
    } else {
        qDebug() << "no se envio PLAY";  // deberia mostrarle un mensaje al usuario
        return false;
    }
}

matchSetup::~matchSetup() { delete ui; }
