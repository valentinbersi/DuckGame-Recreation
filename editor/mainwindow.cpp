#include "mainwindow.h"

#include <QAbstractButton>
#include <QAction>
#include <QDrag>

#include "levelscene.h"
#include "ui_mainwindow.h"
#include "Object.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    auto* scene = new LevelScene(this, 100, 100);
    ui->graphicsView->setScene(scene);

    Object platform("Platform", 2, 2, ":/icons/platformIcon.png");
    Object spawnDuck("SpawnDuck", 4, 2, ":/icons/duckIcon.png");
    Object spawnGun("SpawnGun", 3, 3, ":/icons/gunIcon.png");
    Object box("Box", 2, 2, ":/icons/boxIcon.png");

    // Configura los íconos en la barra de herramientas
    ui->Platform->setIcon(QIcon(platform.icon));
    ui->SpawnDuck->setIcon(QIcon(spawnDuck.icon));
    ui->SpawnGun->setIcon(QIcon(spawnGun.icon));
    ui->Box->setIcon(QIcon(box.icon));

    // Conexiones de acciones de la barra de herramientas
    connect(ui->Platform, &QAction::triggered, this, [scene, platform]() { scene->addObject(platform); });
    connect(ui->SpawnDuck, &QAction::triggered, this, [scene, spawnDuck]() { scene->addObject(spawnDuck); });
    connect(ui->SpawnGun, &QAction::triggered, this, [scene, spawnGun]() { scene->addObject(spawnGun); });
    connect(ui->Box, &QAction::triggered, this, [scene, box]() { scene->addObject(box); });

}

MainWindow::~MainWindow() { delete ui; }