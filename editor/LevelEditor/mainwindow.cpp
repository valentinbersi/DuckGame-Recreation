#include "mainwindow.h"
#include <QAbstractButton>
#include <QAction>
#include "levelscene.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    auto* scene = new LevelScene(this); // esto tendria que ser personalizable.
    ui->graphicsView->setScene(scene);

    // Ejemplo: añado rectángulo a la escena
    connect(ui->addRectButton, &QPushButton::clicked, scene, &LevelScene::addCustomRect);

    // Conexiones de acciones de la barra de herramientas
    connect(ui->Platform, &QAction::triggered, scene, &LevelScene::addPlatform);
    connect(ui->SpawnDuck, &QAction::triggered, scene, &LevelScene::addPlatform);
    connect(ui->SpawnGun, &QAction::triggered, scene, &LevelScene::addPlatform);
    connect(ui->Box, &QAction::triggered, scene, &LevelScene::addPlatform);
    connect(ui->AddRect, &QAction::triggered, scene, &LevelScene::addCustomRect);
}

MainWindow::~MainWindow() { delete ui; }