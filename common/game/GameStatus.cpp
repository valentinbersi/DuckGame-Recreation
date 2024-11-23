#include "GameStatus.h"

#include <utility>

GameStatus::GameStatus(): ServerMessage(MessageType::Game) {}  // Luego chequeamos.

GameStatus::GameStatus(const GameStatus& other):
        ServerMessage(MessageType::Game),
        ducks(other.ducks),
        blockPositions(other.blockPositions),
        itemSpawnerPositions(other.itemSpawnerPositions) {}

GameStatus& GameStatus::operator=(const GameStatus& other) {
    if (this == &other)
        return *this;

    ducks = other.ducks;
    blockPositions = other.blockPositions;
    itemSpawnerPositions = other.itemSpawnerPositions;
    return *this;
}

GameStatus::GameStatus(GameStatus&& other) noexcept:
        ServerMessage(MessageType::Game),
        ducks(std::move(other.ducks)),
        blockPositions(std::move(other.blockPositions)),
        itemSpawnerPositions(std::move(other.itemSpawnerPositions)) {}

GameStatus& GameStatus::operator=(GameStatus&& other) noexcept {
    if (this == &other)
        return *this;

    ducks = std::move(other.ducks);
    blockPositions = std::move(other.blockPositions);
    itemSpawnerPositions = std::move(other.itemSpawnerPositions);
    return *this;
}

bool GameStatus::operator==(const GameStatus& other) const {
    return ducks == other.ducks && blockPositions == other.blockPositions &&
           itemSpawnerPositions == other.itemSpawnerPositions;
}

void GameStatus::send([[maybe_unused]] ServerSendProtocol& serverProtocol) {
    serverProtocol.sendLen(ducks.size());
    for (const auto& duck: ducks) {
        serverProtocol.sendDuckData(duck);
    }

    serverProtocol.sendLen(blockPositions.size());
    for (const auto& blockPosition: blockPositions) {
        serverProtocol.sendBlock(blockPosition);
    }

    serverProtocol.sendLen(itemSpawnerPositions.size());
    for (const auto& spawnPosition: itemSpawnerPositions) {
        serverProtocol.sendBlock(spawnPosition);
    }
}
