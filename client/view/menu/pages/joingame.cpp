#include "joingame.h"

joinGame::joinGame(QWidget* parent): QWidget(parent), ui(new Ui::joinGame) {
    ui->setupUi(this);

    connect(ui->btnJugar_3, &QPushButton::clicked, this, &joinGame::playMatchClicked);
    connect(ui->btnVolver_3, &QPushButton::clicked, this, &joinGame::backClicked);
}

joinGame::~joinGame() { delete ui; }
