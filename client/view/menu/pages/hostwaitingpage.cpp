#include "hostwaitingpage.h"

#include <QDebug>
#include <QMessageBox>

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

    connect(ui->playButton, &QPushButton::clicked, this, &hostWaitingPage::requestStartGame);
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

   qDebug() << "LobbyMessage - STARTMATCH Request:";
   qDebug() << "Players Number:" << message->playerCount;
   qDebug() << "Player 1 Name:" << QString::fromStdString(message->player1Name);
   qDebug() << "Player 2 Name:" << QString::fromStdString(message->player2Name);
   qDebug() << "Match ID:" << message->matchId;

   if (!communicator.trysend(std::move(message))) {
       qDebug() << "Error al enviar el mensaje.";
       return; // chequear que hacer aca!
   }

    while (true) {
        ReplyMessage replyMessage = communicator.recvSync();

        if (replyMessage.matchID != gameInfo.matchID) {
            qDebug() << "Mensaje recibido de otro matchID";
            continue;
        }

        if (replyMessage.startGame == 1) {
            emit startMatch();
            return;
        } else if (replyMessage.startGame == 0) {
            ui->labelPlayersConnected->setText(
                    QString("PLAYERS CONNECTED: %1 / 4").arg(replyMessage.connectedPlayers)
            );
        }
    }
}

hostWaitingPage::~hostWaitingPage() { delete ui; }
