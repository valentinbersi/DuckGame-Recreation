#ifndef DUCKGAME_MAINMENU_H
#define DUCKGAME_MAINMENU_H

#include "ui_mainMenu.h"

#include <QWidget>


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
    void exit();

private:
    Ui::mainMenu* ui;
};


#endif  // DUCKGAME_MAINMENU_H
