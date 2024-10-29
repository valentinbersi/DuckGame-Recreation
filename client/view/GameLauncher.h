#ifndef DUCKGAME_GAMELAUNCHER_H
#define DUCKGAME_GAMELAUNCHER_H

#include "menu/LobbyQT.h"
#include "game/Game.hpp"
#include "../../common/socket/ActiveSocket.h"

class GameLauncher : public QObject {
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
