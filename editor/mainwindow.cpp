#include "mainwindow.h"

#include <QAbstractButton>
#include <QAction>
#include <QDrag>
#include <QScrollBar>

#include "MapExporter.h"
#include "Object.h"
#include "ObjectConstants.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    mapHeight = 50;
    mapWidth = 50;    //esto despues tengo que hacerlo que lo elija el usuario

    scene = new LevelScene(this, mapWidth, mapHeight, objects);
    ui->graphicsView->setScene(scene);

    ui->Platform->setIcon(QIcon(PLATFORM_ICON));
    ui->SpawnDuck->setIcon(QIcon(DUCK_ICON));
    ui->SpawnGun->setIcon(QIcon(ARMAMENT_ICON));
    ui->Box->setIcon(QIcon(BOX_ICON));

//    connect(ui->Platform, &QAction::triggered, this, [this]() {
//        scene->addObject(PLATFORM);
//    });
//
//    connect(ui->SpawnDuck, &QAction::triggered, this, [this]() {
//        scene->addObject(DUCK);
//    });
//
//    connect(ui->SpawnGun, &QAction::triggered, this, [this]() {
//        scene->addObject(ARMAMENT);
//    });
//
//    connect(ui->Box, &QAction::triggered, this, [this]() {
//        scene->addObject(BOX);
//    });

    connect(ui->Platform, &QAction::triggered, this, [this]() {
        scene->toggleAddingObject(PLATFORM);
    });

    connect(ui->SpawnDuck, &QAction::triggered, this, [this]() {
        scene->toggleAddingObject(DUCK);
    });

    connect(ui->SpawnGun, &QAction::triggered, this, [this]() {
        scene->toggleAddingObject(ARMAMENT);
    });

    connect(ui->Box, &QAction::triggered, this, [this]() {
        scene->toggleAddingObject(BOX);
    });

    connect(scene, &LevelScene::addingObjectChanged, this, [this](ObjectType type, bool isAdding) {
        ui->SpawnDuck->setChecked(type == DUCK && isAdding);
        ui->Platform->setChecked(type == PLATFORM && isAdding);
        ui->SpawnGun->setChecked(type == ARMAMENT && isAdding);
        ui->Box->setChecked(type == BOX && isAdding);
    });

    connect(ui->ClearAll, &QAction::triggered, scene, &LevelScene::clearAll);

    connect(ui->SaveMap, &QAction::triggered, this, [this](){
        MapExporter::exportMap(objects, ui->lineEditMapName->text().toStdString(), mapWidth, mapHeight);
    });
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    scene->setSceneRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
}
MainWindow::~MainWindow() {
    delete scene;
    delete ui;
}