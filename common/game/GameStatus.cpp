#include "GameStatus.h"

#include <utility>

GameStatus::GameStatus(): ServerMessage(MessageType::Game) {}

GameStatus::GameStatus(const GameStatus& other):
        ServerMessage(MessageType::Game),
        roundEnded(other.roundEnded),
        gameEnded(other.gameEnded),
        setEnded(other.setEnded),
        ducks(other.ducks),
        itemPositions(other.itemPositions),
        blockPositions(other.blockPositions),
        itemSpawnerPositions(other.itemSpawnerPositions),
        boxPositions(other.boxPositions) {}

GameStatus& GameStatus::operator=(const GameStatus& other) {
    if (this == &other)
        return *this;

    roundEnded = other.roundEnded;
    gameEnded = other.gameEnded;
    setEnded = other.setEnded;
    ducks = other.ducks;
    itemPositions = other.itemPositions;
    blockPositions = other.blockPositions;
    itemSpawnerPositions = other.itemSpawnerPositions;
    boxPositions = other.boxPositions;
    return *this;
}

GameStatus::GameStatus(GameStatus&& other) noexcept:
        ServerMessage(MessageType::Game),
        roundEnded(std::move(other.roundEnded)),
        gameEnded(std::move(other.gameEnded)),
        setEnded(std::move(other.setEnded)),
        ducks(std::move(other.ducks)),
        itemPositions(std::move(other.itemPositions)),
        blockPositions(std::move(other.blockPositions)),
        itemSpawnerPositions(std::move(other.itemSpawnerPositions)),
        boxPositions(std::move(other.boxPositions)) {}

GameStatus& GameStatus::operator=(GameStatus&& other) noexcept {
    if (this == &other)
        return *this;

    roundEnded = std::move(other.roundEnded);
    gameEnded = std::move(other.gameEnded);
    setEnded = std::move(other.setEnded);
    ducks = std::move(other.ducks);
    itemPositions = std::move(other.itemPositions);
    blockPositions = std::move(other.blockPositions);
    itemSpawnerPositions = std::move(other.itemSpawnerPositions);
    boxPositions = std::move(other.boxPositions);
    return *this;
}

bool GameStatus::operator==(const GameStatus& other) const {
    return roundEnded == other.roundEnded && gameEnded == other.gameEnded &&
           setEnded == other.setEnded && ducks == other.ducks &&
           itemPositions == other.itemPositions && blockPositions == other.blockPositions &&
           itemSpawnerPositions == other.itemSpawnerPositions && boxPositions == other.boxPositions;
}

template <typename T>
void GameStatus::sendList(ServerSendProtocol& serverProtocol, const std::list<T>& list,
                          void (ServerSendProtocol::*sendFunc)(const T&)) {
    serverProtocol.sendLen(list.size());
    for (const auto& item: list) {
        (serverProtocol.*sendFunc)(item);
    }
}

void GameStatus::send(ServerSendProtocol& serverProtocol) {
    serverProtocol.sendRoundData(roundEnded, setEnded, gameEnded);
    sendList(serverProtocol, ducks, &ServerSendProtocol::sendDuckData);
    sendList(serverProtocol, itemPositions, &ServerSendProtocol::sendItemData);
    sendList(serverProtocol, blockPositions, &ServerSendProtocol::sendBlock);
    sendList(serverProtocol, itemSpawnerPositions, &ServerSendProtocol::sendBlock);
    sendList(serverProtocol, boxPositions, &ServerSendProtocol::sendBlock);
}
