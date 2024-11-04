#include "joinwaitingpage.h"

#include "ui_joinwaitingpage.h"

joinWaitingPage::joinWaitingPage(QWidget* parent): QWidget(parent), ui(new Ui::joinWaitingPage) {
    ui->setupUi(this);

    // aca deberia llamar al comunicador y bloquearse esperando un message de que inicia la partida.
}

joinWaitingPage::~joinWaitingPage() { delete ui; }
