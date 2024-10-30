#include "newgame.h"

newGame::newGame(QWidget* parent): QWidget(parent), ui(new Ui::newGame) {
    ui->setupUi(this);

    connect(ui->btnJugar_2, &QPushButton::clicked, this, &newGame::playMatchClicked);
    connect(ui->btnVolver_2, &QPushButton::clicked, this, &newGame::backClicked);
}

newGame::~newGame() { delete ui; }
