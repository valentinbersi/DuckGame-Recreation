#include <exception>
#include <iostream>

#include "game/Game.hpp"
#include "menu/LobbyQT.h"
#include "ActiveSocket.h"

int main(int argc, char* argv[]) {
    bool startSDL = false;

    ActiveSocket socket(argv[1], argv[2]);

    LobbyQT lobby(argc, argv);

    QObject::connect(&lobby, &LobbyQT::initMatch, [&]() {
        startSDL = true;
    });

    lobby.exec();

    if (startSDL) {
        try {
            Game game(std::move(socket));
            //two players? lo debo mandar al game
            //debo recibir la cantidad de patos que hay en la partida para pintar N patos distintos
            game.init();

            // Here all resources are automatically released and library deinitialized
            return 0;

        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }
    }
    return 0;
}

/*
#include "GameLauncher.h"

int main(int argc, char* argv[]) {
    cppstring hostname = argv[1];
    cppstring servname = argv[2];

    GameLauncher launcher(argc, argv, hostname, servname);
    launcher.exec();

    return 0;
}*/