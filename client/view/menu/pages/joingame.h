#ifndef DUCKGAME_JOINGAME_H
#define DUCKGAME_JOINGAME_H

#include <QWidget>

#include "GameInfo.h"
#include "MyLobbyMessage.h"
#include "ui_joinGame.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class joinGame;
}
QT_END_NAMESPACE

class joinGame: public QWidget {
    Q_OBJECT

private:
    Ui::joinGame* ui;
    void verificarDatos();
    LobbyMessage_& message;

    void onPlayClicked();

public:
    joinGame(QWidget* parent, LobbyMessage_& message);
    ~joinGame() override;

signals:
    void playMatchClicked();
    void backClicked();

};


#endif  // DUCKGAME_JOINGAME_H
