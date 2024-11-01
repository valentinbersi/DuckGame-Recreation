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
    connect(&lobby, &LobbyQT::initMatch, this, &GameLauncher::startedSDL);
}

void GameLauncher::exec() {
    lobby.exec();

    if (startGame) {
        try {
            communicator.trysend(std::make_unique<LobbyMessage>(LobbyRequest::NEWMATCH, 2, "tomas", "camilo", 1));
            communicator.trysend(std::make_unique<LobbyMessage>(LobbyRequest::STARTMATCH, 2, "andres", "valentin", 1));
            Game game(communicator);
            game.init();

            //return 0;

        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            //return 1;
        }
    }
}

void GameLauncher::startedSDL() {
    startGame = true;
}