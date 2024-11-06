#include "joingame.h"

#include <QDebug>
#include <QMessageBox>

#include "ReplyMessage.h"

joinGame::joinGame(QWidget* parent, Communicator& communicator, GameInfo& gameInfo):
        QWidget(parent),
        ui(new Ui::joinGame),
        communicator(communicator),
        gameInfo(gameInfo) {
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
    gameInfo.player2Name = ui->lineEditPlayer2->text().isEmpty() ? "" : ui->lineEditPlayer2->text().toStdString();
    gameInfo.matchID = ui->lineEditMatchID->text().toUShort();

    qDebug() << "info:" << QString(gameInfo.player1Name.c_str()) << QString(gameInfo.player2Name.c_str()) << gameInfo.matchID;
    if (joinMatchRequest())
        emit playMatchClicked();

    //emit playMatchClicked();
}

bool joinGame::joinMatchRequest() {
    auto message = std::make_unique<LobbyMessage>(
            LobbyRequest::JOINMATCH,
            gameInfo.playersNumber,
            gameInfo.player1Name,
            gameInfo.player2Name,
            gameInfo.matchID // esto deberia ser 0 ¿?
    );
    qDebug() << "joinMatchRequest";
    qDebug() << "matchID del message:" << message->matchId;

    if (!communicator.trysend(std::move(message))) {
        qDebug() << "Error al enviar el mensaje.";
        return false;
    }

    // auto messageServerOpt = communicator.tryrecv();
    // if (messageServerOpt.has_value()) {
    //     std::unique_ptr<ServerMessage> messageServer = std::move(messageServerOpt.value());
    //     ReplyMessage reply = dynamic_cast<ReplyMessage&>(*messageServer);
    //     gameInfo.matchID = reply.matchID;
    //     return true;
    // } else {
    //     QMessageBox::warning(this, "Error", "No se recibió respuesta del servidor.");
    //     return false; // esto nose si es correcto, deberia manejarlo distinto yo creo.
    // }

    qDebug() << "se pide el mensaje reply al comunicador";
    auto messageServerOpt = communicator.recv();
    qDebug() << "se recibio reply";
    const auto* reply = dynamic_cast<const ReplyMessage*>(messageServerOpt.get());
    if(reply == nullptr){
        QMessageBox::warning(this, "Error", "No se recibió respuesta del servidor.");
        return false;
    }
    if(gameInfo.matchID == reply->matchID && reply->startGame == 0)
        return true;
    else
        return false;
}

joinGame::~joinGame() { delete ui; }
