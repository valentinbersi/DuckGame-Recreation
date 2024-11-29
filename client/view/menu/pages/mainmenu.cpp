#include "mainmenu.h"

#include <QDebug>
#include <QMessageBox>

mainMenu::mainMenu(QWidget* parent): QWidget(parent), ui(new Ui::mainMenu) {
    ui->setupUi(this);

    connect(ui->btnJugar, &QPushButton::clicked, this, &mainMenu::play);
    connect(ui->btnExit, &QPushButton::clicked, this, &mainMenu::handleExit);
}

void mainMenu::handleExit() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Salir", "¿Seguro que querés salir?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        emit exitGameRequested();
    }
}

mainMenu::~mainMenu() { delete ui; }
