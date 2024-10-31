#include "configurationpage.h"

#include <QButtonGroup>


configurationPage::configurationPage(QWidget* parent, LobbyMessage_& message):
        QWidget(parent),
        ui(new Ui::configurationPage),
        message(message) {
    ui->setupUi(this);

    CantidadPlayersGroup = new QButtonGroup(this);
    CantidadPlayersGroup->addButton(ui->radio1Player, 1);
    CantidadPlayersGroup->addButton(ui->radio2Player, 2);
    ui->radio1Player->setChecked(true);

    connect(ui->btnUnirse, &QPushButton::clicked, this, &configurationPage::handleJoinGame);
    connect(ui->btnCrear, &QPushButton::clicked, this, &configurationPage::handleNewGame);
    connect(ui->btnVolver, &QPushButton::clicked, this, &configurationPage::backClicked);
}

int configurationPage::getSelectedPlayers() const {
    return CantidadPlayersGroup->checkedId();  // Devuelve el ID del botón seleccionado
}

void configurationPage::handleJoinGame() {
    message.setPlayerCount(getSelectedPlayers());
    emit joinGameClicked();
}

void configurationPage::handleNewGame() {
    message.setPlayerCount(getSelectedPlayers());
    emit newGameClicked();
}

configurationPage::~configurationPage() { delete ui; }
