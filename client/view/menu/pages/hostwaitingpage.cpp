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

    connect(ui->playButton, &QPushButton::clicked, this, &hostWaitingPage::requestStartGame);
}

void hostWaitingPage::requestStartGame() {
    emit startMatch();

    // ESTO LO COMENTO AHORA MIENTRAS NO PROBEMOS QUE FUNCIONA,
    // PERO ES MAS O MENOS LO QUE IRIA PARA COMUNICARSE CON EL SERVER Y INICIAR LA PARTIDA

//    auto message = std::make_unique<LobbyMessage>(
//            LobbyRequest::STARTMATCH,
//            gameInfo.playersNumber,
//            gameInfo.player1Name,
//            gameInfo.player2Name,
//            gameInfo.matchID
//            );
//
//    if (!communicator.trysend(std::move(message))) {
//        qDebug() << "Error al enviar el mensaje.";
//        return; // chequear que hacer aca!
//    }
//
//    auto messageServerOpt = communicator.tryrecv();
//    if (messageServerOpt.has_value()) {
//        std::unique_ptr<ServerMessage> messageServer = std::move(messageServerOpt.value());
//        ReplyMessage reply = dynamic_cast<ReplyMessage&>(*messageServer);
//        if (reply.startGame == 1) {
//            emit startMatch();
//        } else {
//            // ver que hacer aca!
//        }
//    } else {
//        QMessageBox::warning(this, "Error", "No se recibió respuesta del servidor.");
//        return; // esto nose si es correcto, deberia manejarlo distinto yo creo.
//    }
}

hostWaitingPage::~hostWaitingPage() { delete ui; }
