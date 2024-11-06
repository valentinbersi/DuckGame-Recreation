#include "newgame.h"

#include <QDebug>
#include <QMessageBox>
#include <QStringListModel>

#include "ReplyMessage.h"

newGame::newGame(QWidget* parent, Communicator& communicator, GameInfo& gameInfo): QWidget(parent), ui(new Ui::newGame), communicator(communicator), gameInfo(gameInfo) {
    ui->setupUi(this);

    // esto tendriamos que recibirlo desde el server, nose cuando
    QStringList mapas = {"Selva", "Bosque", "Nave Espacial"};
    auto modeloMapas = new QStringListModel(mapas, this);
    ui->mapsList->setModel(modeloMapas);

    connect(ui->buttonPlay, &QPushButton::clicked, this, &newGame::onPlayClicked);
    connect(ui->buttonBack, &QPushButton::clicked, this, &newGame::backClicked);
}

bool newGame::verificarDatos() {
    bool mapaSeleccionado = !ui->mapsList->selectionModel()->selectedIndexes().isEmpty();
    bool jugador1Ingresado = !ui->lineEditPlayer1->text().isEmpty();

    bool jugador2Ingresado = true;
    if (gameInfo.playersNumber == 2)
        jugador2Ingresado = !ui->lineEditPlayer2->text().isEmpty();

    return (mapaSeleccionado && jugador1Ingresado && jugador2Ingresado);
}

void newGame::onPlayClicked() {
    if (!verificarDatos()) {
        QMessageBox::warning(this, "Datos incompletos",
                             "Por favor, completa todos los datos antes de continuar.");
        return;
    }

    gameInfo.player1Name = ui->lineEditPlayer1->text().toStdString();
    gameInfo.player2Name = ui->lineEditPlayer2->text().isEmpty() ? "" : ui->lineEditPlayer2->text().toStdString();

    QModelIndexList selectedIndexes = ui->mapsList->selectionModel()->selectedIndexes();
    if (!selectedIndexes.isEmpty()) {
        QString selectedMap = selectedIndexes.first().data().toString();
        gameInfo.selectedMap = selectedMap.toStdString();
    }

   if (NewMatchRequest())   //ESTO ESTA COMENTADO PARA PROBARLO CUANDO ESTE EL SERVER
       emit playMatchClicked();

    // emit playMatchClicked();   // esto no iria despues!
}

bool newGame::NewMatchRequest() {
    auto message = std::make_unique<LobbyMessage>(
            LobbyRequest::NEWMATCH,
            gameInfo.playersNumber,
            gameInfo.player1Name,
            gameInfo.player2Name,
            gameInfo.matchID // esto deberia ser 0 ¿?
    );

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

    auto messageServerOpt = communicator.recv();
    const ReplyMessage* reply = dynamic_cast<const ReplyMessage*>(messageServerOpt.get());
    if(reply == nullptr){
        QMessageBox::warning(this, "Error", "No se recibió respuesta del servidor.");
        return false;
    }
    gameInfo.matchID = reply->matchID;
    return true;
}


newGame::~newGame() { delete ui; }
