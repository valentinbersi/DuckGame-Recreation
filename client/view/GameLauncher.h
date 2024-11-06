#ifndef DUCKGAME_GAMELAUNCHER_H
#define DUCKGAME_GAMELAUNCHER_H

#include "ActiveSocket.h"
#include "../game/Game.hpp"
#include "Communicator.h"
#include "QApplication"
#include "gameMenu.h"

class GameLauncher: public QObject {
    Q_OBJECT

private:
    Communicator communicator;
    QApplication app;
    bool twoPlayersLocal;
    GameMenu menu;
    bool startGame;

public:
    GameLauncher(int argc, char* argv[], cppstring hostname, cppstring servname);
    void exec();

private slots:
    void startedSDL();
};

#endif  // DUCKGAME_GAMELAUNCHER_H
