#ifndef DUCKGAME_JOINGAME_H
#define DUCKGAME_JOINGAME_H

#include <QWidget>

#include "Communicator.h"
#include "GameInfo.h"
#include "LobbyMessage.h"
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
    Communicator& communicator;
    GameInfo& gameInfo;

    bool verificarDatos();
    void onPlayClicked();
    bool joinMatchRequest();

public:
    joinGame(QWidget* parent, Communicator& communicator, GameInfo& gameInfo);
    ~joinGame() override;

signals:
    void playMatchClicked();
    void backClicked();


};


#endif  // DUCKGAME_JOINGAME_H
