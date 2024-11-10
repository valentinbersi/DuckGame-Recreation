#include "hostwaitingpage.h"

#include <QDebug>
#include <QMessageBox>
#include <QTimer>

#include "LobbyMessage.h"
#include "ReplyMessage.h"
#include "common_init.h"
#include "ui_hostwaitingpage.h"


hostWaitingPage::hostWaitingPage(QWidget* parent, Communicator& communicator, GameInfo& gameInfo):
        QWidget(parent),
        ui(new Ui::hostWaitingPage),
        communicator(communicator),
        gameInfo(gameInfo){
    ui->setupUi(this);

    ui->labelMatchID->setText(QString("MATCH ID: %1").arg(gameInfo.matchID));

    auto* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &hostWaitingPage::updateConnectedPlayers);
    timer->start(5000);

    connect(ui->playButton, &QPushButton::clicked, this, &hostWaitingPage::requestStartGame);
}


void hostWaitingPage::updateConnectedPlayers() {
    try {
        ReplyMessage messageServer = communicator.recvSync(); // aca iria el tryRecvLobby o lo que fuese
        // deberia chequear que se recibio algo, si se recibio actualizo el label.
        ui->labelPlayersConnected->setText(QString("PLAYERS CONNECTED: %1 / 4").arg(messageServer.connectedPlayers));
    } catch (const LibError& e) {
        qDebug() << "Error receiving message: " << e.what();
    }
}

// USAR ESTA CUANDO SE QUIERE PROBAR SIN SERVER
//void hostWaitingPage::requestStartGame() {
//    emit startMatch();
//}

// USAR ESTA PARA CORRER CON SERVER
void hostWaitingPage::requestStartGame() {
   auto message = std::make_unique<LobbyMessage>(
           LobbyRequest::STARTMATCH,
           gameInfo.playersNumber,
           gameInfo.player1Name,
           gameInfo.player2Name,
           gameInfo.matchID
           );

   try {
       communicator.sendSync(std::move(message));
   } catch (LibError& libError){
       qDebug() << "Error sending start game request: " << libError.what();
       return; // aca podria mostrar elgun mensaje
   }

   ReplyMessage replyMessage;
   try {
       replyMessage = communicator.recvSync();
   } catch (LibError& libError) {
       qDebug() << "Error receiving start game response: " << libError.what();
       return;
   }

    if (replyMessage.startGame == 1) {
        emit startMatch();
        return;
    }
}

hostWaitingPage::~hostWaitingPage() { delete ui; }
