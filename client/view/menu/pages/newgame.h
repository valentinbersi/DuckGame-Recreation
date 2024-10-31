//
// Created by tomas-hevia on 25/10/24.
//

#ifndef DUCKGAME_NEWGAME_H
#define DUCKGAME_NEWGAME_H

#include <QWidget>

#include "GameInfo.h"
#include "MyLobbyMessage.h"
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
    LobbyMessage_& message;

    void verificarDatos();
    void onPlayClicked();

public:
    newGame(QWidget* parent, LobbyMessage_& message);
    ~newGame() override;

signals:
    void playMatchClicked();
    void backClicked();
};


#endif  // DUCKGAME_NEWGAME_H
