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
    serverProtocol.sendLen(ducks.size());
    for (const auto& duck: ducks) {
        serverProtocol.sendDuckData(duck);
    }

    serverProtocol.sendLen(blockPositions.size());
    for (const auto& blockPosition: blockPositions) {
        serverProtocol.sendVector2(blockPosition);
    }
}
