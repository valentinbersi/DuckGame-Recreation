#include "ViewController.h"

#include <QAbstractButton>
#include <QAction>
#include <QDrag>
#include <QFileDialog>
#include <QFileInfo>
#include <QListWidget>
#include <QMessageBox>
#include <QScrollBar>
#include <QWheelEvent>

#include "EditorConstants.h"
#include "MapManager.h"
#include "Object.h"
#include "ui_viewcontroller.h"
#include "Background.h"
#include "Resource.h"

//#define BUTTONS_STYLE R"(
// QPushButton {
//    background-color: rgb(229, 165, 10);
//    border-radius: 5px;
//}
// QPushButton:checked {
//    background-color: rgb(165, 29, 45);
//})"


ViewController::ViewController(QWidget* parent):
        QMainWindow(parent),
        ui(new Ui::ViewController),
        mapManager(mapData),
        backgroundBrush(Qt::white) {
    ui->setupUi(this);

    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
    // scene = new LevelScene(this, objects);
    scene = new LevelScene(this, mapData.objects);
    ui->graphicsView->setScene(scene);
    onSceneResize();
    setupToolBar();
    loadBackgrounds();

    connect(scene, &LevelScene::requestDragModeChange, ui->graphicsView,
            &QGraphicsView::setDragMode);

    connect(ui->actionSaveMap, &QAction::triggered, this,
            &ViewController::on_actionSaveMap_triggered);
    connect(ui->actionNewMap, &QAction::triggered, this,
            &ViewController::on_actionNewMap_triggered);
    connect(ui->actionEditMap, &QAction::triggered, this,
            &ViewController::on_actionEditMap_triggered);

    connect(ui->ClearAll, &QAction::triggered, scene, &LevelScene::clearAll);
    //connect(ui->ChangeBackground, &QAction::triggered, this, &ViewController::selectBackground);

    connect(scene, &LevelScene::resizeView, this, &ViewController::onSceneResize);
}

void ViewController::loadBackgrounds() {
    for (int i = BackgroundID::CascadeCave; i <= BackgroundID::Sunset; i++) {
        BackgroundID background((BackgroundID::Value)i);
        std::string backgroundPath = Resource::get().resource(background.path());
        QPixmap pixmap(QString::fromStdString(backgroundPath));
        if (!pixmap.isNull()) {
            QString fileName = QFileInfo(QString::fromStdString(backgroundPath)).completeBaseName();

            auto *item = new QListWidgetItem(QIcon(pixmap), fileName);
            item->setData(Qt::UserRole, (BackgroundID::Value)i);
            ui->backgroundList->addItem(item);
        }
    }
    connect(ui->backgroundList, &QListWidget::itemClicked, this, &ViewController::onBackgroundSelected);
}

void ViewController::onBackgroundSelected(QListWidgetItem *item) {
    BackgroundID backgroundSelected((BackgroundID::Value)item->data(Qt::UserRole).toInt());
    mapData.backgroundID = backgroundSelected;
    changeBackgroundBrush();
}

void ViewController::changeBackgroundBrush() {
    std::string backgroundPath = Resource::get().resource(mapData.backgroundID.path());
    QPixmap pixmap(QString::fromStdString(backgroundPath));

    if (pixmap.isNull()) {
        QMessageBox::warning(this, "Error", "The selected file is not a valid image.");
        return;
    }

    QPixmap scaledPixmap = pixmap.scaled(ui->centralwidget->size(), Qt::KeepAspectRatioByExpanding,
                                         Qt::SmoothTransformation);
    backgroundBrush = QBrush(scaledPixmap);
    update();
}

void ViewController::setupToolBar() {
    platformButton = new QPushButton(QIcon(PLATFORM_ICON), "", this);
    spawnDuckButton = new QPushButton(QIcon(DUCK_ICON), "", this);
    spawnArmamentButton = new QPushButton(QIcon(ARMAMENT_ICON), "", this);
    boxButton = new QPushButton(QIcon(BOX_ICON), "", this);

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
        // button->setStyleSheet(QString(BUTTONS_STYLE));
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

void ViewController::on_actionSaveMap_triggered() {
    if (!scene->enoughDucks()) {
        QMessageBox::warning(this, "Error", "The map should have 4 duck spawns.");
        return;
    }
    mapData.name = ui->lineEditMapName->text().toStdString();
    mapManager.exportMap();
    QMessageBox::information(this, "Save Map", "The map was saved successfully!");
}

bool ViewController::confirmAndSaveMap() {
    QMessageBox::StandardButton reply =
            QMessageBox::question(this, "Confirmation", "Do you want to save the map open?",
                                  QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (reply == QMessageBox::Cancel) {
        return false;
    } else if (reply == QMessageBox::Yes) {
        mapData.name = ui->lineEditMapName->text().toStdString();
        mapManager.exportMap();
    }
    return true;
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

    //QString fileName = QFileDialog::getOpenFileName(this, "Select Map", "/home/", "Archivos YAML (*.yaml)");

    QString fileName = QFileDialog::getOpenFileName(this, "Select Map", "maps/", "Archivos YAML (*.yaml)");

    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Error", "There was an error importing the map.");
        return;
    }

    mapData.path = fileName.toStdString();
    scene->clearAll();

    bool success = mapManager.importMap();
    if (!success)
        return;

    scene->loadMap(mapData.width, mapData.height);
    onSceneResize();
    changeBackgroundBrush();
    ui->lineEditMapName->setText(QString::fromStdString(mapData.name));
    QMessageBox::information(this, "Imported Map", "The map has been imported successfully!");
}

void ViewController::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    QPainter painter(this);
    painter.save();

    painter.setBrush(backgroundBrush);
    painter.drawRect(this->rect());

    painter.restore();
}

ViewController::~ViewController() {
    delete scene;
    delete ui;
    delete platformButton;
    delete spawnDuckButton;
    delete spawnArmamentButton;
    delete boxButton;
}
