#include "mainwindow.h"

#include <QAbstractButton>
#include <QAction>
#include <QDrag>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QScrollBar>
#include <QWheelEvent>

#include "EditorConstants.h"
#include "MapManager.h"
#include "Object.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent): QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    scene = new LevelScene(this, objects);
    ui->graphicsView->setScene(scene);
    onSceneResize();

    setActionButtons();

    connect(ui->ClearAll, &QAction::triggered, scene, &LevelScene::clearAll);

    connect(ui->actionSaveMap, &QAction::triggered, this, [this]() {
        if (!scene->enoughDucks()) {
            QMessageBox::warning(this, "Error", "The map should have 4 duck spawns.");
            return;
        }
        MapManager::exportMap(objects, ui->lineEditMapName->text().toStdString(),
                              scene->getMapWidth(), scene->getMapHeight());
    });

    connect(ui->actionNewMap, &QAction::triggered, this, &MainWindow::on_actionNewMap_triggered);

    connect(ui->actionEditMap, &QAction::triggered, this, &MainWindow::on_actionEditMap_triggered);

    connect(scene, &LevelScene::resizeView, this, &MainWindow::onSceneResize);
}

void MainWindow::setActionButtons() {
    actionTypeMap = {{ui->Platform, PLATFORM},
                     {ui->SpawnDuck, DUCK},
                     {ui->SpawnGun, ARMAMENT},
                     {ui->Box, BOX}};

    ui->Platform->setIcon(QIcon(PLATFORM_ICON));
    ui->SpawnDuck->setIcon(QIcon(DUCK_ICON));
    ui->SpawnGun->setIcon(QIcon(ARMAMENT_ICON));
    ui->Box->setIcon(QIcon(BOX_ICON));

    for (const auto& [action, type]: actionTypeMap) {
        connect(action, &QAction::triggered, this,
                [this, type]() { scene->selectObjectType(type); });
    }

    connect(scene, &LevelScene::addingObjectChanged, this, [this](ObjectType type) {
        for (const auto& [action, objType]: actionTypeMap) {
            action->setChecked(objType == type);
        }
    });
}

void MainWindow::onSceneResize() {
    QRectF sceneRect = scene->sceneRect();
    ui->graphicsView->setSceneRect(0, 0, sceneRect.width() * 4, sceneRect.height() * 4);
}

void MainWindow::on_actionNewMap_triggered() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Do you want to save the map open?",
                                  QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (reply == QMessageBox::Cancel)
        return;
    else if (reply == QMessageBox::Yes)
        MapManager::exportMap(objects, ui->lineEditMapName->text().toStdString(),
                              scene->getMapWidth(), scene->getMapHeight());
    scene->clearAll();
    ui->lineEditMapName->clear();
    QMessageBox::information(this, "New Map", "A new map was created!");
}

void MainWindow::on_actionEditMap_triggered() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmation", "Do you want to save the map open?",
                                  QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes)
        MapManager::exportMap(objects, ui->lineEditMapName->text().toStdString(),
                              scene->getMapWidth(), scene->getMapHeight());
    else if (reply == QMessageBox::Cancel)
        return;

    QString fileName =
            QFileDialog::getOpenFileName(this, "Select Map", "maps/", "Archivos YAML (*.yaml)");

    if (!fileName.isEmpty()) {
        QFileInfo fileInfo(fileName);
        QString mapName = fileInfo.baseName();

        scene->clearAll();

        int mapWidth;
        int mapHeight;
        bool success = MapManager::importMap(objects, fileName.toStdString(), mapWidth, mapHeight,
                                             background);
        if (success) {
            scene->loadMap(mapWidth, mapHeight);
            ui->lineEditMapName->setText(mapName);
            QMessageBox::information(this, "Imported Map",
                                     "The map has been imported successfully!");
        } else {
            QMessageBox::warning(this, "Error", "There was an error importing the map.");
        }
    }
}

MainWindow::~MainWindow() {
    delete scene;
    delete ui;
}

/*
void MainWindow::wheelEvent(QWheelEvent* event) {
    if (event->modifiers() & Qt::ControlModifier) {
        qreal zoomFactor = 1.15;

QPointF viewCenter =
        ui->graphicsView->mapToScene(ui->graphicsView->viewport()->rect().center());

if (event->angleDelta().y() > 0)
    ui->graphicsView->scale(zoomFactor, zoomFactor);
else
    ui->graphicsView->scale(1 / zoomFactor, 1 / zoomFactor);

QPointF newCenter = ui->graphicsView->mapFromScene(viewCenter);
ui->graphicsView->ensureVisible(newCenter.x(), newCenter.y(), 100, 100, 1.0);

event->accept();
} else {
    QMainWindow::wheelEvent(event);
}
}
*/
