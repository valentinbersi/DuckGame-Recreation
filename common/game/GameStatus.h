#pragma once

#include <list>

#include "ServerMessage.h"

/**
 * A struct with the current game status.
 */
struct GameStatus final: ServerMessage {
    GameStatus();
    GameStatus(const GameStatus& other);
    GameStatus& operator=(const GameStatus& other);
    GameStatus(GameStatus&& other) noexcept;
    GameStatus& operator=(GameStatus&& other) noexcept;

    std::list<DuckData> ducks;
    std::list<Vector2> blockPositions;

    void send(ServerSendProtocol& serverProtocol) override;
};
