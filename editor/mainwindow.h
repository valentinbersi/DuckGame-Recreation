#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "MapManager.h"
#include "levelscene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow* ui;
    int mapHeight;
    int mapWidth;
    std::string background;
    std::vector<Object> objects;
    LevelScene* scene;
    std::map<QAction*, ObjectType> actionTypeMap;

    void resizeEvent(QResizeEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;
    void on_actionNewMap_triggered();
    void on_actionEditMap_triggered();
    void setActionButtons();
};
#endif  // MAINWINDOW_H
