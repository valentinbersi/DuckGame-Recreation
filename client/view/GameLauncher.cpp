#include "GameLauncher.h"

#include <iostream>

#include "GameLauncher.h"

//GameLauncher::GameLauncher(int argc, char* argv[], cppstring hostname,
//                           cppstring servname):
//        socket(hostname, servname),
//        communicator(std::move(socket)),
//        lobby(argc, argv, communicator),
//        game(communicator) {
//    connect(&lobby, &LobbyQT::initMatch, this, &GameLauncher::onInitMatch);
//}
//
//void GameLauncher::exec() { lobby.exec(); }
//
//void GameLauncher::onInitMatch() {
//    try {
////        Game game(communicator);
//        game.init();
//    } catch (std::exception& e) {
//        std::cerr << e.what() << std::endl;
//    }
//}

GameLauncher::GameLauncher(int argc, char* argv[], cppstring hostname,
                           cppstring servname):
        communicator(hostname, servname),
        lobby(argc, argv, communicator) {
    connect(&lobby, &LobbyQT::initMatch, this, &GameLauncher::onInitMatch);
}

void GameLauncher::exec() {
    lobby.exec();
}

void GameLauncher::onInitMatch() {
    try {
        Game game(communicator);  // Instancia `Game` solo cuando el lobby finaliza
        game.init();              // Inicia el juego
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}