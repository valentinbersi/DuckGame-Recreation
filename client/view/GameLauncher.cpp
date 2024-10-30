#include "GameLauncher.h"

#include <iostream>

#include "GameLauncher.h"

GameLauncher::GameLauncher(int argc, char* argv[], const cppstring hostname,
                           const cppstring servname):
        socket(hostname, servname), lobby(argc, argv /*, socket*/) {
    connect(&lobby, &LobbyQT::initMatch, this, &GameLauncher::onInitMatch);
}

void GameLauncher::exec() { lobby.exec(); }

void GameLauncher::onInitMatch() {
    try {
        Game game(std::move(socket));
        game.init();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}