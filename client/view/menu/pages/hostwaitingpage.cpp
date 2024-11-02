//
// Created by tomas-hevia on 1/11/24.
//

// You may need to build the project (run Qt uic code generator) to get "ui_hostwaitingpage.h"
// resolved

#include "hostwaitingpage.h"

#include "ui_hostwaitingpage.h"


hostWaitingPage::hostWaitingPage(QWidget* parent): QWidget(parent), ui(new Ui::hostWaitingPage) {
    ui->setupUi(this);
}

hostWaitingPage::~hostWaitingPage() { delete ui; }
