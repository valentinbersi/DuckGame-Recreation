#include "mainwindow.h"

#include <QAbstractButton>
#include <QAction>
#include <QDrag>
#include <QScrollBar>
#include <QWheelEvent>

#include "MapExporter.h"
#include "Object.h"
#include "ObjectConstants.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    scene = new LevelScene(this, objects);
    ui->graphicsView->setScene(scene);

    qDebug() << "Current graphicsView:" << ui->graphicsView->sceneRect();

    // ESTO PODRIA PONERLO DIRECTAMENTE EN EL UI CREO
    //ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::NoAnchor);

    ui->Platform->setIcon(QIcon(PLATFORM_ICON));
    ui->SpawnDuck->setIcon(QIcon(DUCK_ICON));
    ui->SpawnGun->setIcon(QIcon(ARMAMENT_ICON));
    ui->Box->setIcon(QIcon(BOX_ICON));

    connect(ui->Platform, &QAction::triggered, this, [this]() {
        scene->toggleAddingObject(PLATFORM);
        qDebug() << "Current graphicsView:" << ui->graphicsView->sceneRect();
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
    QRectF sceneRect = scene->sceneRect();
    ui->graphicsView->setSceneRect(0, 0, sceneRect.width() * 2, sceneRect.height() * 2);
}

void MainWindow::wheelEvent(QWheelEvent* event) {
    if (event->modifiers() & Qt::ControlModifier) { // Si Ctrl está presionado
        qreal zoomFactor = 1.15;

        QPointF viewCenter = ui->graphicsView->mapToScene(ui->graphicsView->viewport()->rect().center());

        if (event->angleDelta().y() > 0) {
            ui->graphicsView->scale(zoomFactor, zoomFactor); // Acercar
        } else {
            ui->graphicsView->scale(1 / zoomFactor, 1 / zoomFactor); // Alejar
        }

        QPointF newCenter = ui->graphicsView->mapFromScene(viewCenter);
        ui->graphicsView->ensureVisible(newCenter.x(), newCenter.y(), 100, 100, 1.0);

        event->accept();
    } else {
        QMainWindow::wheelEvent(event); // Comportamiento por defecto
    }
}

MainWindow::~MainWindow() {
    delete scene;
    delete ui;
}