//
// Created by tomas-hevia on 25/10/24.
//

#ifndef DUCKGAME_NEWGAME_H
#define DUCKGAME_NEWGAME_H

#include <QWidget>

#include "GameInfo.h"
#include "LobbyMessage.h"
#include "ui_newGame.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class newGame;
}
QT_END_NAMESPACE

class newGame: public QWidget {
    Q_OBJECT

private:
    Ui::newGame* ui;
    GameInfo& gameInfo;

    void verificarDatos();
    void onPlayClicked();

public:
    newGame(QWidget* parent, GameInfo& gameInfo);
    ~newGame() override;

signals:
    void playMatchClicked();
    void backClicked();
};


#endif  // DUCKGAME_NEWGAME_H
