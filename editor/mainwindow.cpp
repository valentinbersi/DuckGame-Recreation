#include "mainwindow.h"

#include <QAbstractButton>
#include <QAction>
#include <QDrag>
#include <QScrollBar>

#include "MapExporter.h"
#include "Object.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    mapHeight = 50;
    mapWidth = 50;    //esto despues tengo que hacerlo que lo elija el usuario

    scene = new LevelScene(this, mapWidth, mapHeight, objects);
    ui->graphicsView->setScene(scene);

    Object platform(PLATFORM, 2, 2, ":/icons/platformIcon.png");
    Object spawnDuck(DUCK, 3, 2, ":/icons/duckIcon.png");
    Object spawnGun(GUN, 3, 3, ":/icons/gunIcon.png");
    Object box(BOX, 2, 2, ":/icons/boxIcon.png");

    ui->Platform->setIcon(QIcon(platform.icon));
    ui->SpawnDuck->setIcon(QIcon(spawnDuck.icon));
    ui->SpawnGun->setIcon(QIcon(spawnGun.icon));
    ui->Box->setIcon(QIcon(box.icon));

    connect(ui->Platform, &QAction::triggered, this, [this, platform]() { scene->addObject(platform); });
    connect(ui->SpawnDuck, &QAction::triggered, this, [this, spawnDuck]() { scene->addObject(spawnDuck); });
    connect(ui->SpawnGun, &QAction::triggered, this, [this, spawnGun]() { scene->addObject(spawnGun); });
    connect(ui->Box, &QAction::triggered, this, [this, box]() { scene->addObject(box); });

    connect(ui->SaveMap, &QAction::triggered, this, [this]() { MapExporter::exportMap(objects, ui->lineEditMapName->text().toStdString(), mapWidth, mapHeight); });
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
}
MainWindow::~MainWindow() {
    delete scene;
    delete ui;
}