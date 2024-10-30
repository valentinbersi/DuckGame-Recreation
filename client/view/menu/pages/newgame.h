//
// Created by tomas-hevia on 25/10/24.
//

#ifndef DUCKGAME_NEWGAME_H
#define DUCKGAME_NEWGAME_H

#include <QWidget>

#include "ui_newGame.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class newGame;
}
QT_END_NAMESPACE

class newGame: public QWidget {
    Q_OBJECT

public:
    explicit newGame(QWidget* parent = nullptr);
    ~newGame() override;

signals:
    void playMatchClicked();
    void backClicked();

private:
    Ui::newGame* ui;
};


#endif  // DUCKGAME_NEWGAME_H
