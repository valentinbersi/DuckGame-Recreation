#include <exception>
#include <iostream>
#include "view/game/Game.hpp"

#include "view/menu/LobbyQT.h"

int main(int argc, char* argv[]) {
    bool startSDL = false;

    LobbyQT lobby(argc, argv);

    QObject::connect(&lobby, &LobbyQT::initMatch, [&]() {
        startSDL = true;
    });

    lobby.exec();

    if (startSDL) {
        try {
            Game game;
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
