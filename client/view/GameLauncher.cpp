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
    app.exec();

    if (startGame) {
        try {
            qDebug() << "twoPlayerLocal is" << twoPlayersLocal;
            Game game(communicator, twoPlayersLocal);
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