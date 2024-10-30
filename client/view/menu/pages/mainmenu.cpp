#include "mainmenu.h"

mainMenu::mainMenu(QWidget* parent): QWidget(parent), ui(new Ui::mainMenu) {
    ui->setupUi(this);

    connect(ui->btnJugar, &QPushButton::clicked, this, &mainMenu::play);
    connect(ui->btnExit, &QPushButton::clicked, this, &mainMenu::exit);
}

mainMenu::~mainMenu() { delete ui; }
