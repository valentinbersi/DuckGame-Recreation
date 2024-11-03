#include "GameLauncher.h"
#include <iostream>

GameLauncher::GameLauncher(int argc, char* argv[], cppstring hostname,
                           cppstring servname):
        communicator(hostname, servname),
        app(argc, argv),
        menu(nullptr, communicator),
        startGame(false){
    connect(&menu, &GameMenu::startGame, this, &GameLauncher::startedSDL);
    menu.show();
}

void GameLauncher::exec() {
    app.exec();

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