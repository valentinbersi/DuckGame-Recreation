#include "waitingPage.h"

#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <memory>
#include <utility>

#include "LobbyMessage.h"
#include "ReplyMessage.h"
#include "ui_waitingPage.h"


WaitingPage::WaitingPage(QWidget* parent, Communicator& communicator,
                         GameInfo& gameInfo):
        QWidget(parent),
        ui(new Ui::WaitingPage),
        communicator(communicator),
        gameInfo(gameInfo),
        timer(new QTimer(this)) {
    ui->setupUi(this);

    ui->labelMatchID->setText(QString("MATCH ID: %1").arg(gameInfo.matchID));

    connect(timer, &QTimer::timeout, this, &WaitingPage::recvServerMessage);
    timer->start(1000);

    if (!gameInfo.isNewGame)
        ui->playButton->setVisible(false);
    else
        connect(ui->playButton, &QPushButton::clicked, this, &WaitingPage::requestStartGame);
}

void WaitingPage::recvServerMessage() {
    std::optional<ReplyMessage> replyMessageOpt = communicator.tryRecvReply();

    if (replyMessageOpt.has_value()) {
        ReplyMessage message = replyMessageOpt.value();
        ui->labelPlayersConnected->setText(
                QString("PLAYERS CONNECTED: %1 / 4").arg(message.connectedPlayers));

        if (message.startGame == 1) {
            emit startMatch();
            timer->stop();
        }

//        if (gameInfo.isNewGame && message.connectedPlayers == 4)
//            requestStartGame();

    } else {
        qDebug() << "replyMessage is NULL";
    }  // esto nose si va
}

void WaitingPage::requestStartGame() {
    auto message = std::make_unique<LobbyMessage>(LobbyRequest::STARTMATCH, gameInfo.playersNumber,
                                                  gameInfo.player1Name, gameInfo.player2Name,
                                                  gameInfo.matchID);

    communicator.trysend(std::move(message));
    // tengo que chequear si se envio bien?
    ui->playButton->setEnabled(false);
}

WaitingPage::~WaitingPage() { delete ui; }
