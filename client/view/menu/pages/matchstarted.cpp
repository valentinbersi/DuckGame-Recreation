#include "matchstarted.h"
#include "../common_init.h"

matchStarted::matchStarted(QWidget* parent): QWidget(parent), ui(new Ui::matchStarted) {
    ui->setupUi(this);
}

matchStarted::~matchStarted() { delete ui; }
