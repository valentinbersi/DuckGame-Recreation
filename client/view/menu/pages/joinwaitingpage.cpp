#include "joinwaitingpage.h"

#include <QMessageBox>

#include "ReplyMessage.h"
#include "ui_joinwaitingpage.h"

joinWaitingPage::joinWaitingPage(QWidget* parent, Communicator& communicator):
        QWidget(parent),
        ui(new Ui::joinWaitingPage),
        communicator(communicator) {
    ui->setupUi(this);
}

void joinWaitingPage::waitForMatchStart() {
    while (true) {
        ReplyMessage replyMessage = communicator.recvSync();

        if (replyMessage.connectedPlayers > 0) {
            ui->labelPlayersConnected->setText(QString("Player Connected: %1").arg(replyMessage.connectedPlayers));
        } else {
            QMessageBox::warning(this, "Error", "No se recibió respuesta del servidor.");
            break; // nose si esta bien esto!
        }

        if (replyMessage.startGame == 1) {
            emit matchStarted();
            break;
        }
    }
}

joinWaitingPage::~joinWaitingPage() { delete ui; }
