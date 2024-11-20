#include "GameStatus.h"

#include <utility>

GameStatus::GameStatus(): ServerMessage(MessageType::Game) {}  // Luego chequeamos.

GameStatus::GameStatus(const GameStatus& other):
        ServerMessage(MessageType::Game),
        ducks(other.ducks),
        blockPositions(other.blockPositions) {}

GameStatus& GameStatus::operator=(const GameStatus& other) {
    if (this == &other)
        return *this;

    ducks = other.ducks;
    blockPositions = other.blockPositions;
    return *this;
}

GameStatus::GameStatus(GameStatus&& other) noexcept:
        ServerMessage(MessageType::Game),
        ducks(std::move(other.ducks)),
        blockPositions(std::move(other.blockPositions)) {}

GameStatus& GameStatus::operator=(GameStatus&& other) noexcept {
    if (this == &other)
        return *this;

    ducks = std::move(other.ducks);
    blockPositions = std::move(other.blockPositions);
    return *this;
}

void GameStatus::send([[maybe_unused]] ServerSendProtocol& serverProtocol) {
    // TODO: implement if necessary

    // serverProtocol.sendLen(gameObjects.size());
    // for (const auto& object: gameObjects) {
    //     serverProtocol.sendDuck(*object);
    // }
}
