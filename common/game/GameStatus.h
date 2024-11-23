#pragma once

#include <list>

#include "DuckData.h"
#include "ServerMessage.h"
#include "SizedObjectData.h"

/**
 * A struct with the current game status.
 */
struct GameStatus final: ServerMessage {
    GameStatus();
    GameStatus(const GameStatus& other);
    GameStatus& operator=(const GameStatus& other);
    GameStatus(GameStatus&& other) noexcept;
    GameStatus& operator=(GameStatus&& other) noexcept;
    bool operator==(const GameStatus& other) const;

    std::list<DuckData> ducks;
    std::list<SizedObjectData> blockPositions;
    std::list<SizedObjectData> itemSpawnerPositions;

    void send(ServerSendProtocol& serverProtocol) override;
};
