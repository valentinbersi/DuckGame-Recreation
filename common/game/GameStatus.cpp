#include "GameStatus.h"

#include <utility>

GameStatus::GameStatus(): ServerMessage(MessageType::Game) {}  // Luego chequeamos.

GameStatus::GameStatus(GameStatus&& other) noexcept:
        ServerMessage(MessageType::Game), gameObjects(std::move(other.gameObjects)) {}

GameStatus& GameStatus::operator=(GameStatus&& other) noexcept {
    if (this == &other)
        return *this;

    gameObjects = std::move(other.gameObjects);
    return *this;
}

void GameStatus::send(ServerSendProtocol& serverProtocol) {
    serverProtocol.sendLen(gameObjects.size());
    for (const auto& object: gameObjects) {
        serverProtocol.sendDuck(*object);
    }
}
