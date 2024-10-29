#ifndef DUCKGAME_JOINGAME_H
#define DUCKGAME_JOINGAME_H

#include "ui_joinGame.h"

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui {
class joinGame;
}
QT_END_NAMESPACE

class joinGame: public QWidget {
    Q_OBJECT

public:
    explicit joinGame(QWidget* parent = nullptr);
    ~joinGame() override;

signals:
    void playMatchClicked();
    void backClicked();

private:
    Ui::joinGame* ui;
};


#endif  // DUCKGAME_JOINGAME_H
