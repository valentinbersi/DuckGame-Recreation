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
    auto messageServerOpt = communicator.recv();
    ReplyMessage* reply = dynamic_cast<ReplyMessage*>(messageServerOpt.get());
    if (reply != nullptr && reply->startGame == 1) {
        emit matchStarted();
    } else {
        QMessageBox::warning(this, "Error", "No se recibió respuesta del servidor.");
        return;
    }
}

joinWaitingPage::~joinWaitingPage() { delete ui; }
