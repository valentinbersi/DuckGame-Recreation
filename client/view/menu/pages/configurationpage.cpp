#include "configurationpage.h"

#include <QButtonGroup>
#include <QMessageBox>
#include <QDebug>


configurationPage::configurationPage(QWidget* parent, GameInfo& gameInfo, Communicator& communicator):
        QWidget(parent), ui(new Ui::configurationPage), gameInfo(gameInfo), communicator(communicator) {
    ui->setupUi(this);

    CantidadPlayersGroup = new QButtonGroup(this);
    CantidadPlayersGroup->addButton(ui->radio1Player, 1);
    CantidadPlayersGroup->addButton(ui->radio2Player, 2);
    ui->radio1Player->setChecked(true);

    connect(ui->btnJoin, &QPushButton::clicked, this, &configurationPage::handlerJoinGame);
    connect(ui->btnCreate, &QPushButton::clicked, this, &configurationPage::handlerNewGame);
    connect(ui->btnVolver, &QPushButton::clicked, this, &configurationPage::backClicked);
}


int configurationPage::getSelectedPlayers() const { return CantidadPlayersGroup->checkedId(); }

void configurationPage::handlerJoinGame() {
    if (ui->lineEditMatchID->text().isEmpty()) {
        QMessageBox::warning(this, "No se ingreso un Match ID",
                             "Por favor, ingresa un Match ID antes de continuar.");
        return;
    }
    gameInfo.playersNumber = getSelectedPlayers();
    gameInfo.matchID = ui->lineEditMatchID->text().toUShort();
    LobbyRequest request(LobbyRequest::JOINMATCH);
    if (initMatchRequest(request)) {
        gameInfo.isNewGame = false;
        emit playMatchClicked();
    }
}

void configurationPage::handlerNewGame() {
    gameInfo.playersNumber = getSelectedPlayers();
    LobbyRequest request(LobbyRequest::NEWMATCH);
    if (initMatchRequest(request)) {
        gameInfo.isNewGame = true;
        emit playMatchClicked();
    }
}

bool configurationPage::initMatchRequest(LobbyRequest& request) {
    auto message = std::make_unique<LobbyMessage>(request, gameInfo.playersNumber,
                                                  gameInfo.matchID);
    qDebug() << message->request << message->playerCount << message->matchId;
    if (communicator.trysend(std::move(message))) {
        // chequear si se envio ¿?
        ReplyMessage replyMessage = communicator.blockingRecv();
        /** chequear si se recibio bien (chequear colores y string de error) */
        gameInfo.matchID = replyMessage.matchID;
        return true;
    } else {
        qDebug() << "no se envio PLAY";  // deberia mostrarle un mensaje al usuario
        return false;
    }
}

configurationPage::~configurationPage() {
    delete CantidadPlayersGroup;
    delete ui;
}
