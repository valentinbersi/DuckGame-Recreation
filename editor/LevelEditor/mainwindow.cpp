#include "mainwindow.h"

#include <QAbstractButton>

#include "levelscene.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    auto *scene = new LevelScene(this);
    ui->graphicsView->setScene(scene);

    //scene->addRect(0,0,100,100); // ejemplo: añado rectangulo a la escena
    connect(ui->addRectButton, &QPushButton::clicked, scene, &LevelScene::addCustomRect);
}

MainWindow::~MainWindow() { delete ui; }
