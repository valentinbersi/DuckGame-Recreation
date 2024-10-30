#ifndef DUCKGAME_GAMELAUNCHER_H
#define DUCKGAME_GAMELAUNCHER_H

#include "../../common/socket/ActiveSocket.h"
#include "game/Game.hpp"
#include "menu/LobbyQT.h"

class GameLauncher: public QObject {
    Q_OBJECT

public:
    GameLauncher(int argc, char* argv[], const cppstring hostname, const cppstring servname);
    void exec();

private slots:
    void onInitMatch();

private:
    ActiveSocket socket;
    LobbyQT lobby;
};

#endif  // DUCKGAME_GAMELAUNCHER_H
