#include <exception>
#include <iostream>
#include "view/game/Game.hpp"

int main() try {
    Game game;
    game.init();

    // Here all resources are automatically released and library deinitialized
    return 0;

} catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;
}
