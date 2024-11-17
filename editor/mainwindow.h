#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "MapExporter.h"
#include "levelscene.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow: public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow* ui;
    int mapHeight;
    int mapWidth;
    std::vector<Object> objects;
    LevelScene* scene;
    MapExporter mapExporter; // esto capaz no es necesario!
    void resizeEvent(QResizeEvent* event) override;
};
#endif  // MAINWINDOW_H
