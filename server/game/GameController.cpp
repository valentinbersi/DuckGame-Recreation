#include "GameController.h"

#include <iostream>
#include <memory>
#include <string>

GameController::~GameController() = default;

GameController::GameController() = default;

void GameController::start() { std::cout << "The game has started" << std::endl; }

void GameController::update(const float delta) {
    std::cout << "The game is running" << delta << std::endl;
}

void GameController::addPlayer(const PlayerID playerID) {
    const std::string id = std::to_string(playerID);

    addChild(id, std::make_unique<Player>());
    players[playerID] = dynamic_cast<Player*>(getChild(id));
}
