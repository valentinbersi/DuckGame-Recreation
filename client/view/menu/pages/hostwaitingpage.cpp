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
        gameInfo(gameInfo),
        timer(new QTimer(this)){
    ui->setupUi(this);

    ui->labelMatchID->setText(QString("MATCH ID: %1").arg(gameInfo.matchID));

    connect(timer, &QTimer::timeout, this, &hostWaitingPage::recvServerMessage);
    timer->start(1000);

    connect(ui->playButton, &QPushButton::clicked, this, &hostWaitingPage::requestStartGame);
}

void hostWaitingPage::recvServerMessage() {
    std::optional<ReplyMessage> replyMessageOpt = communicator.tryRecvReply();

    if (replyMessageOpt.has_value()) {
        ReplyMessage message = replyMessageOpt.value();
        ui->labelPlayersConnected->setText(QString("PLAYERS CONNECTED: %1 / 4").arg(message.connectedPlayers));

        if (message.startGame == 1) {
            emit startMatch();
            timer->stop();
        }

        if (message.connectedPlayers == 4)
            requestStartGame();

    } else {qDebug() << "replyMessage is NULL";}
}

void hostWaitingPage::requestStartGame() {
   auto message = std::make_unique<LobbyMessage>(
           LobbyRequest::STARTMATCH,
           gameInfo.playersNumber,
           gameInfo.player1Name,
           gameInfo.player2Name,
           gameInfo.matchID
           );
   communicator.trysend(std::move(message));
   // tengo que chequear si se envio bien?
}

hostWaitingPage::~hostWaitingPage() { delete ui; }
