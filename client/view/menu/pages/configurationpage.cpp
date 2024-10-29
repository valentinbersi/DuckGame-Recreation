#include "configurationpage.h"

#include <QButtonGroup>


configurationPage::configurationPage(QWidget* parent):
        QWidget(parent), ui(new Ui::configurationPage) {
    ui->setupUi(this);

    CantidadPlayersGroup = new QButtonGroup(this);
    CantidadPlayersGroup->addButton(ui->radio1Player, 1);
    CantidadPlayersGroup->addButton(ui->radio2Player, 2);
    ui->radio1Player->setChecked(true);

    connect(ui->btnUnirse, &QPushButton::clicked, this, &configurationPage::joinGameClicked);
    connect(ui->btnCrear, &QPushButton::clicked, this, &configurationPage::newGameClicked);
    connect(ui->btnVolver, &QPushButton::clicked, this, &configurationPage::backClicked);

}

int configurationPage::getSelectedPlayers() const {
    return CantidadPlayersGroup->checkedId(); // Devuelve el ID del botón seleccionado
}

configurationPage::~configurationPage() { delete ui; }
