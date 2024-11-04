#ifndef DUCKGAME_NEWGAME_H
#define DUCKGAME_NEWGAME_H

#include <QWidget>

#include "Communicator.h"
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
    Communicator& communicator;
    GameInfo& gameInfo;

    bool verificarDatos();
    void onPlayClicked();
    bool NewMatchRequest();

public:
    newGame(QWidget* parent, Communicator& communicator, GameInfo& gameInfo);
    ~newGame() override;

signals:
    void playMatchClicked();
    void backClicked();
};


#endif  // DUCKGAME_NEWGAME_H
