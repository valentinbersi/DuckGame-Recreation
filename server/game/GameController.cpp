#include "GameController.h"

#include <iostream>
#include <memory>
#include <string>

#include "GameStatus.h"

GameController::~GameController() = default;

GameController::GameController() = default;

void GameController::start() { std::cout << "The game has started" << std::endl; }

void GameController::update(const float delta) {
    std::cout << "The game is running" << delta << std::endl;
}

void GameController::updateInternal([[maybe_unused]] float delta) {}

void GameController::addPlayer(const PlayerID playerID) {
    const std::string id = std::to_string(playerID);

    addChild(id, std::make_unique<Player>());
    players[playerID] = dynamic_cast<Player*>(&getChild(id));
}

GameStatus GameController::status() {
    GameStatus status;

    std::ranges::for_each(getChildren(), [&status](const auto& child) {
        status.gameObjects.splice(status.gameObjects.end(),
                                  std::move(std::move(child.second->status()).gameObjects));
    });

    return status;
}
