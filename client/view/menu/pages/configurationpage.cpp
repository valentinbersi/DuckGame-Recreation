#include "configurationpage.h"

#include <QButtonGroup>


configurationPage::configurationPage(QWidget* parent, GameInfo& gameInfo):
        QWidget(parent), ui(new Ui::configurationPage), gameInfo(gameInfo) {
    ui->setupUi(this);

    CantidadPlayersGroup = new QButtonGroup(this);
    CantidadPlayersGroup->addButton(ui->radio1Player, 1);
    CantidadPlayersGroup->addButton(ui->radio2Player, 2);
    ui->radio1Player->setChecked(true);

    connect(ui->btnUnirse, &QPushButton::clicked, this, &configurationPage::handleJoinGame);
    connect(ui->btnCrear, &QPushButton::clicked, this, &configurationPage::handleNewGame);
    connect(ui->btnVolver, &QPushButton::clicked, this, &configurationPage::backClicked);
}

int configurationPage::getSelectedPlayers() const { return CantidadPlayersGroup->checkedId(); }

void configurationPage::handleJoinGame() {
    gameInfo.playersNumber = getSelectedPlayers();
    emit joinGameClicked();
}

void configurationPage::handleNewGame() {
    gameInfo.playersNumber = getSelectedPlayers();
    emit newGameClicked();
}

configurationPage::~configurationPage() { delete ui; }
