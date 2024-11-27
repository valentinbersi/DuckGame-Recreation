#include "ViewController.h"

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
#include "ui_viewcontroller.h"

#define BUTTONS_STYLE \
    R"(
QPushButton {
    background-color: transparent;
    border: none;
    border-radius: 10px;
}

QPushButton:checked {
    background-color: rgb(165, 29, 45);
}
)"

ViewController::ViewController(QWidget* parent):
        QMainWindow(parent), ui(new Ui::ViewController), backgroundBrush(Qt::white) {
    ui->setupUi(this);

    ui->graphicsView->setBackgroundBrush(Qt::NoBrush);
    scene = new LevelScene(this, objects);
    ui->graphicsView->setScene(scene);
    onSceneResize();

    setupToolBar();

    connect(ui->ClearAll, &QAction::triggered, scene, &LevelScene::clearAll);

    connect(ui->actionSaveMap, &QAction::triggered, this, [this]() {
        if (!scene->enoughDucks()) {
            QMessageBox::warning(this, "Error", "The map should have 4 duck spawns.");
            return;
        }
        MapManager::exportMap(objects, ui->lineEditMapName->text().toStdString(),
                              scene->getMapWidth(), scene->getMapHeight());
        QMessageBox::information(this, "Save Map", "El mapa se guardo correctamente!");
    });

    connect(ui->actionNewMap, &QAction::triggered, this,
            &ViewController::on_actionNewMap_triggered);

    connect(ui->actionEditMap, &QAction::triggered, this,
            &ViewController::on_actionEditMap_triggered);

    connect(scene, &LevelScene::resizeView, this, &ViewController::onSceneResize);

    connect(ui->ChangeBackground, &QAction::triggered, this, &ViewController::changeBackground);
}

void ViewController::setupToolBar() {
    QPushButton* platformButton = new QPushButton(QIcon(PLATFORM_ICON), "", this);
    QPushButton* spawnDuckButton = new QPushButton(QIcon(DUCK_ICON), "", this);
    QPushButton* spawnArmamentButton = new QPushButton(QIcon(ARMAMENT_ICON), "", this);
    QPushButton* boxButton = new QPushButton(QIcon(BOX_ICON), "", this);

    ui->toolBar->addWidget(platformButton);
    ui->toolBar->addWidget(spawnDuckButton);
    ui->toolBar->addWidget(spawnArmamentButton);
    ui->toolBar->addWidget(boxButton);

    buttonTypeMap = {{platformButton, PLATFORM},
                     {spawnDuckButton, DUCK},
                     {spawnArmamentButton, ARMAMENT},
                     {boxButton, BOX}};

    for (const auto& [button, type]: buttonTypeMap) {
        button->setCheckable(true);
        button->setIconSize(QSize(64, 64));
        button->setStyleSheet(BUTTONS_STYLE);
        connect(button, &QPushButton::clicked, this,
                [this, type]() { scene->selectObjectType(type); });
    }

    connect(scene, &LevelScene::addingObjectChanged, this, [this](ObjectType type) {
        for (const auto& [action, objType]: buttonTypeMap) {
            action->setChecked(objType == type);
        }
    });
}

void ViewController::onSceneResize() {
    QRectF sceneRect = scene->sceneRect();
    ui->graphicsView->setSceneRect(0, 0, sceneRect.width() * 4, sceneRect.height() * 4);
}

bool ViewController::confirmAndSaveMap() {
    QMessageBox::StandardButton reply =
            QMessageBox::question(this, "Confirmation", "Do you want to save the map open?",
                                  QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (reply == QMessageBox::Cancel)
        return false;
    else if (reply == QMessageBox::Yes)
        MapManager::exportMap(objects, ui->lineEditMapName->text().toStdString(),
                              scene->getMapWidth(), scene->getMapHeight());
    return true;
}

void ViewController::changeBackground() {
    QString filePath = QFileDialog::getOpenFileName(this, "Select Backgrounds",
                                                    "assets/background/", "Images (*.png)");
    if (filePath.isEmpty()) {
        QMessageBox::information(this, "No Background Selected",
                                 "Please select an image from the assets folder.");
        return;
    }

    QPixmap pixmap(filePath);
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "Error", "The selected file is not a valid image.");
        return;
    }
    backgroundBrush = QBrush(pixmap);
    update();
}

void ViewController::on_actionNewMap_triggered() {
    if (!confirmAndSaveMap())
        return;

    scene->clearAll();
    ui->lineEditMapName->clear();
    QMessageBox::information(this, "New Map", "A new map was created!");
}

void ViewController::on_actionEditMap_triggered() {
    if (!confirmAndSaveMap())
        return;

    QString fileName =
            QFileDialog::getOpenFileName(this, "Select Map", "maps/", "Archivos YAML (*.yaml)");

    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Error", "There was an error importing the map.");
        return;
    }

    QFileInfo fileInfo(fileName);
    QString mapName = fileInfo.baseName();

    scene->clearAll();

    int mapWidth;
    int mapHeight;
    bool success =
            MapManager::importMap(objects, fileName.toStdString(), mapWidth, mapHeight, background);
    if (!success)
        return;

    scene->loadMap(mapWidth, mapHeight);
    ui->lineEditMapName->setText(mapName);
    QMessageBox::information(this, "Imported Map", "The map has been imported successfully!");
}

ViewController::~ViewController() {
    delete scene;
    delete ui;
}

void ViewController::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.save();

    painter.setBrush(backgroundBrush);
    painter.drawRect(this->rect());

    painter.restore();
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
