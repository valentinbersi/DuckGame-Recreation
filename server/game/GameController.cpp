#include "GameController.h"

#include <iostream>
#include <memory>
#include <string>

#include "GameStatus.h"

GameController::~GameController() = default;

GameController::GameController(): Object(nullptr){};

void GameController::start() { std::cout << "The game has started" << std::endl; }

void GameController::update(const float delta) {
    std::cout << "The game is running" << delta << std::endl;
}

#define FULL_GAME "The game is full"

#define MAX_PLAYERS 4

void GameController::addPlayer(const PlayerID playerID) {
    const std::string id = std::to_string(playerID);

    if (players.size() >= MAX_PLAYERS)
        throw std::logic_error(FULL_GAME);

    auto duckID = static_cast<DuckID>(players.size());

    addChild(id, std::make_unique<Player>(duckID));
    players[playerID] = dynamic_cast<Player*>(&getChild(id));
}

Player& GameController::getPlayer(const PlayerID playerID) const { return *players.at(playerID); }

u8 GameController::playersCount() const { return players.size(); }

GameStatus GameController::status() {
    GameStatus status;

    forAllChildren([&status](Object& child) {
        status.gameObjects.splice(status.gameObjects.end(),
                                  std::move(std::move(child.status()).gameObjects));
    });

    return status;
}
