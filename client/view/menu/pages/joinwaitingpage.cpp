//
// Created by tomas-hevia on 1/11/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_joinwaitingpage.h"
// resolved

#include "joinwaitingpage.h"

#include "ui_joinwaitingpage.h"


joinWaitingPage::joinWaitingPage(QWidget* parent): QWidget(parent), ui(new Ui::joinWaitingPage) {
    ui->setupUi(this);
}

joinWaitingPage::~joinWaitingPage() { delete ui; }
