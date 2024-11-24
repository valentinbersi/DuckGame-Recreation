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
    return ducks == other.ducks && 
           itemPositions == other.itemPositions &&
           blockPositions == other.blockPositions &&
           itemSpawnerPositions == other.itemSpawnerPositions;
}

template<typename T>
void GameStatus::sendList(ServerSendProtocol& serverProtocol, const std::list<T>& list, void (ServerSendProtocol::*sendFunc)(const T&)) {
    serverProtocol.sendLen(list.size());
    for (const auto& item: list) {
        (serverProtocol.*sendFunc)(item);
    }
}

void GameStatus::send(ServerSendProtocol& serverProtocol) {
    sendList(serverProtocol, ducks, &ServerSendProtocol::sendDuckData);
    sendList(serverProtocol, itemPositions, &ServerSendProtocol::sendItemData);
    sendList(serverProtocol, blockPositions, &ServerSendProtocol::sendBlock);
    sendList(serverProtocol, itemSpawnerPositions, &ServerSendProtocol::sendBlock);
}
