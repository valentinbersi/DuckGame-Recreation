#include "ViewController.h"

#include <QAbstractButton>
#include <QDrag>
#include <QFileInfo>
#include <QListWidget>
#include <QMessageBox>
#include <QTimer>
#include <QWheelEvent>

#include "Background.h"
#include "EditorConstants.h"
#include "MapManager.h"
#include "Object.h"
#include "Resource.h"
#include "ui_viewcontroller.h"

ViewController::ViewController(QWidget* parent):
        QMainWindow(parent),
        ui(new Ui::ViewController),
        mapManager(mapData),
        backgroundBrush(Qt::white) {
    ui->setupUi(this);

    ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
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

    connect(scene, &LevelScene::resizeView, this, &ViewController::onSceneResize);

    QTimer::singleShot(0, this, &ViewController::showStartupInfo);
}

void ViewController::showStartupInfo() {
    QString message =
        "Welcome to the Level Editor.\n\n"
        "Basic Controls:\n"
        "- Select/Deselect an object to add: Use the right sidebar.\n"
        "- Add the selected object to the map: Left click (hold and drag to add multiple objects).\n"
        "- Remove an object from the map: Right click (hold and drag to remove multiple objects).\n\n"
        "Keyboard Shortcuts:\n"
        "- New Map: CTRL+N.\n"
        "- Save Map: CTRL+S.\n"
        "- Load/Edit Map: CTRL+E.\n\n"
        "Important Note:\n"
        "It is recommended to save maps in the folder: /etc/DuckGame/maps\n"
        "so the server can load the maps and display them in the game.\n\n"
        "Enjoy creating levels!";

    QMessageBox::information(this, "Editor Instructions", message);
}



void ViewController::loadBackgrounds() {
    for (int i = BackgroundID::CascadeCave; i <= BackgroundID::Sunset; i++) {
        BackgroundID background((BackgroundID::Value)i);
        std::string backgroundPath = Resource::get().resource(background.pathToBackground());
        QPixmap pixmap(QString::fromStdString(backgroundPath));
        if(pixmap.isNull()) continue;

        QString fileName = QFileInfo(QString::fromStdString(backgroundPath)).completeBaseName();
        QListWidgetItem *item = new QListWidgetItem(QIcon(pixmap), fileName);
        item->setData(Qt::UserRole, i);
        ui->backgroundList->addItem(item);
    }
    connect(ui->backgroundList, &QListWidget::itemClicked, this,
            &ViewController::onBackgroundSelected);
}

void ViewController::onBackgroundSelected(const QListWidgetItem* item) {
    const BackgroundID backgroundSelected(static_cast<BackgroundID::Value>(item->data(Qt::UserRole).toInt()));
    mapData.backgroundID = backgroundSelected;
    changeBackgroundBrush();
}

void ViewController::changeBackgroundBrush() {
    std::string backgroundPath = Resource::get().resource(mapData.backgroundID.pathToBackground());
    QPixmap backgroundPixmap(QString::fromStdString(backgroundPath));

    std::string tilePath = Resource::get().resource(mapData.backgroundID.pathToTileset());
    QPixmap platformPixmap(QString::fromStdString(tilePath));

    if (backgroundPixmap.isNull() || platformPixmap.isNull()) {
        QMessageBox::warning(this, "Error", "The selected file is not a valid image.");
        return;
    }

    QPixmap scaledPixmap = backgroundPixmap.scaled(
            ui->centralwidget->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    backgroundBrush = QBrush(scaledPixmap);

    platformButton->setIcon(QIcon(platformPixmap));
    platformButton->update();
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
    if (mapManager.exportMap(this))
        QMessageBox::information(this, "Save Map", "The map was saved successfully!");
    else
        QMessageBox::information(this, "No Save Map", "The map was not saved :(");
}

bool ViewController::confirmAndSaveMap() {
    QMessageBox::StandardButton reply =
            QMessageBox::question(this, "Confirmation", "Do you want to save the map open?",
                                  QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (reply == QMessageBox::Cancel) {
        return false;
    }
    if (reply == QMessageBox::Yes) {
        mapData.name = ui->lineEditMapName->text().toStdString();
        if (mapManager.exportMap(this))
            QMessageBox::information(this, "Save Map", "The map was saved successfully!");
        else
            QMessageBox::information(this, "No Save Map", "The map was not saved :(");
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

    scene->clearAll();

    bool success = mapManager.importMap(this);
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
    ui->backgroundList->clear();
}
