#include "GameLauncher.h"

#include <iostream>

#include <QDebug>

GameLauncher::GameLauncher(int argc, char* argv[], cppstring hostname,
                           cppstring servname):
        communicator(hostname, servname),
        app(argc, argv),
        twoPlayersLocal(false),
        menu(nullptr, communicator, twoPlayersLocal),
        startGame(false){
    connect(&menu, &GameMenu::startGame, this, &GameLauncher::startedSDL);
    menu.show();
}

void GameLauncher::exec() {
    try {
        app.exec();
        if (startGame) {
            Game game(communicator, twoPlayersLocal);
            game.init();
        }
    } catch (const LibError& libError) {
        syslog(LOG_CRIT, "%s", libError.what());
    }
}

void GameLauncher::startedSDL() { startGame = true; }