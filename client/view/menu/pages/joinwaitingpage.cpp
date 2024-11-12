#include "joinwaitingpage.h"

#include <QMessageBox>
#include <QTimer>

#include "ReplyMessage.h"
#include "ui_joinwaitingpage.h"

#include <QDebug>

joinWaitingPage::joinWaitingPage(QWidget* parent, Communicator& communicator)
        : QWidget(parent),
        ui(new Ui::joinWaitingPage),
        communicator(communicator),
        timer(new QTimer(this)) {
    ui->setupUi(this);

    connect(timer, &QTimer::timeout, this, &joinWaitingPage::recvServerMessage);
    timer->start(1000);
}

void joinWaitingPage::recvServerMessage() {
    std::optional<ReplyMessage> replyMessageOpt = communicator.tryRecvReply();

    if (replyMessageOpt.has_value()) {
        ReplyMessage message = replyMessageOpt.value();
        ui->labelPlayersConnected->setText(QString("PLAYERS CONNECTED: %1 / 4").arg(message.connectedPlayers));

        if (message.startGame == 1) {
            emit matchStarted();
            timer->stop();
        }
    } else {qDebug() << "replyMessage is NULL";}
}

joinWaitingPage::~joinWaitingPage() { delete ui; }
