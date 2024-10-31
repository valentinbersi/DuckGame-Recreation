#ifndef DUCKGAME_GAMELAUNCHER_H
#define DUCKGAME_GAMELAUNCHER_H

#include "../../common/socket/ActiveSocket.h"
#include "game/Game.hpp"
#include "LobbyQT.h"
#include "Communicator.h"

class GameLauncher: public QObject {
    Q_OBJECT

private:
    Communicator communicator;
    LobbyQT lobby;

public:
    GameLauncher(int argc, char* argv[], cppstring hostname, cppstring servname);
    void exec();

private slots:
    void onInitMatch();

};

#endif  // DUCKGAME_GAMELAUNCHER_H
