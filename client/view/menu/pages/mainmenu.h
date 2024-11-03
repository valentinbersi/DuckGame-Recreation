#ifndef DUCKGAME_MAINMENU_H
#define DUCKGAME_MAINMENU_H

#include <QWidget>

#include "ui_mainMenu.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class mainMenu;
}
QT_END_NAMESPACE

class mainMenu: public QWidget {
    Q_OBJECT

public:
    explicit mainMenu(QWidget* parent = nullptr);
    ~mainMenu() override;

signals:
    void play();
    void exitGameRequested();

private:
    Ui::mainMenu* ui;
    void handleExit();
};


#endif  // DUCKGAME_MAINMENU_H
