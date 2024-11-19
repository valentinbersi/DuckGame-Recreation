#include "mainwindow.h"

#include <QAbstractButton>
#include <QAction>
#include <QDrag>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QScrollBar>
#include <QWheelEvent>

#include "MapManager.h"
#include "Object.h"
#include "ObjectConstants.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    scene = new LevelScene(this, objects);
    ui->graphicsView->setScene(scene);

    setActionButtons();

    connect(ui->ClearAll, &QAction::triggered, scene, &LevelScene::clearAll);

    connect(ui->actionSaveMap, &QAction::triggered, this, [this](){
        MapManager::exportMap(objects, ui->lineEditMapName->text().toStdString(), mapWidth, mapHeight);
    });

    connect(ui->actionNewMap, &QAction::triggered, this, &MainWindow::on_actionNewMap_triggered);

    connect(ui->actionEditMap, &QAction::triggered, this, &MainWindow::on_actionEditMap_triggered);
}

void MainWindow::setActionButtons() {
    actionTypeMap = {
            {ui->Platform, PLATFORM},
            {ui->SpawnDuck, DUCK},
            {ui->SpawnGun, ARMAMENT},
            {ui->Box, BOX}
    };

    ui->Platform->setIcon(QIcon(PLATFORM_ICON));
    ui->SpawnDuck->setIcon(QIcon(DUCK_ICON));
    ui->SpawnGun->setIcon(QIcon(ARMAMENT_ICON));
    ui->Box->setIcon(QIcon(BOX_ICON));

    for (const auto& [action, type] : actionTypeMap) {
        connect(action, &QAction::triggered, this, [this, type]() {
            scene->selectObjectType(type);
        });
    }

    connect(scene, &LevelScene::addingObjectChanged, this, [this](ObjectType type) {
        for (const auto& [action, objType] : actionTypeMap) {
            action->setChecked(objType == type);
        }
    });
}

void MainWindow::resizeEvent(QResizeEvent* event) {
    QMainWindow::resizeEvent(event);
    QRectF sceneRect = scene->sceneRect();
    ui->graphicsView->setSceneRect(0, 0, sceneRect.width() * 2, sceneRect.height() * 2);
}

void MainWindow::wheelEvent(QWheelEvent* event) {
    if (event->modifiers() & Qt::ControlModifier) {
        qreal zoomFactor = 1.15;

        QPointF viewCenter = ui->graphicsView->mapToScene(ui->graphicsView->viewport()->rect().center());

        if (event->angleDelta().y() > 0) {
            ui->graphicsView->scale(zoomFactor, zoomFactor);
        } else {
            ui->graphicsView->scale(1 / zoomFactor, 1 / zoomFactor);
        }

        QPointF newCenter = ui->graphicsView->mapFromScene(viewCenter);
        ui->graphicsView->ensureVisible(newCenter.x(), newCenter.y(), 100, 100, 1.0);

        event->accept();
    } else {
        QMainWindow::wheelEvent(event);
    }
}

void MainWindow::on_actionNewMap_triggered() {
    if (!objects.empty()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmación",
                                      "Tenes un mapa abierto. ¿Deseas guardarlo antes de abrir uno nuevo?",
                                      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if (reply == QMessageBox::Yes) {
            MapManager::exportMap(objects, ui->lineEditMapName->text().toStdString(), mapWidth, mapHeight);
        } else if (reply == QMessageBox::Cancel) {
            return;
        }
    }

    scene->clearAll();

    QMessageBox::information(this, "Nuevo Mapa", "Se ha creado un nuevo mapa.");
}

void MainWindow::on_actionEditMap_triggered() {
    if (!objects.empty()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Confirmar",
                                      "¿Deseas guardar los cambios del mapa actual antes de importar uno nuevo?",
                                      QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

        if (reply == QMessageBox::Yes) {
            MapManager::exportMap(objects, ui->lineEditMapName->text().toStdString(), mapWidth, mapHeight);
        } else if (reply == QMessageBox::Cancel) {
            return;
        }
    }

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Seleccionar Mapa", "../maps/", "Archivos YAML (*.yaml)");

    if (!fileName.isEmpty()) {
        QFileInfo fileInfo(fileName);
        QString mapName = fileInfo.baseName();

        scene->clearAll();

        bool success = MapManager::importMap(objects, fileName.toStdString(), mapWidth, mapHeight, background);

        if (success) {
            scene->loadMap(mapWidth, mapHeight);
            QMessageBox::information(this, "Mapa Importado", "El mapa se ha importado correctamente.");
        } else {
            QMessageBox::warning(this, "Error", "Hubo un error al importar el mapa.");
        }
    }
}

MainWindow::~MainWindow() {
    delete scene;
    delete ui;
}