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
        QMessageBox::warning(this, "A Match ID was not entered",
                             "Please enter a Match ID before continuing.");
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

QString getColor(DuckData::Id id) {
    switch (id) {
        case DuckData::Id::White:
            return {"white"};
        case DuckData::Id::Grey:
            return {"grey"};
        case DuckData::Id::Orange:
            return {"orange"};
        case DuckData::Id::Yellow:
            return {"yellow"};
        case DuckData::Id::None:
            return {"none"};
    }
    return {"vacio"};
}

bool configurationPage::initMatchRequest(LobbyRequest& request) {
    auto message = std::make_unique<LobbyMessage>(request, gameInfo.playersNumber,
                                                  gameInfo.matchID);
    qDebug() << message->request << message->playerCount << message->matchId;
    if (communicator.trysend(std::move(message))) {
        // chequear si se envio ¿?
        ReplyMessage replyMessage = communicator.blockingRecv();
        if (replyMessage.matchID == 0) {
            QMessageBox::warning(this, "Error", QString::fromStdString(replyMessage.error));
            return false;
        }

        gameInfo.matchID = replyMessage.matchID;
        gameInfo.Duck1Color = replyMessage.color1;
        gameInfo.Duck2Color = replyMessage.color2;
        qDebug() << "color 1:" << getColor(gameInfo.Duck1Color) << "color 2:" << getColor(gameInfo.Duck2Color);
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
