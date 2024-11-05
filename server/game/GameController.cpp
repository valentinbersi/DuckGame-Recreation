#include "GameController.h"

#include <iostream>
#include <memory>
#include <string>

#include "GameStatus.h"

GameController::~GameController() = default;

GameController::GameController(): Object(nullptr){};

void GameController::start() { std::cout << "The game has started" << std::endl; }

void GameController::loadChildren() {}  // This should be empty

void GameController::update(const float delta) {
    std::cout << "The game is running" << delta << std::endl;
}

void GameController::addPlayer(const PlayerID playerID) {
    const std::string id = std::to_string(playerID);

    addChild(id, std::make_unique<Player>());
    players[playerID] = dynamic_cast<Player*>(&getChild(id));
}

Player& GameController::getPlayer(const PlayerID playerID) const { return *players.at(playerID); }

GameStatus GameController::status() {
    GameStatus status;

    forAllChildren([&status](Object& child) {
        status.gameObjects.splice(status.gameObjects.end(),
                                  std::move(std::move(child.status()).gameObjects));
    });

    return status;
}
