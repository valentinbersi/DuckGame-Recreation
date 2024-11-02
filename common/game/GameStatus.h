#pragma once

#include <list>
#include <memory>

#include "GameObjectData.h"
#include "ServerMessage.h"

/**
 * A struct with the current game status.
 */
struct GameStatus: public ServerMessage {
    GameStatus();
    GameStatus(const GameStatus& other) = delete;
    GameStatus& operator=(const GameStatus& other) = delete;
    GameStatus(GameStatus&& other) noexcept;
    GameStatus& operator=(GameStatus&& other) noexcept;

    std::list<std::unique_ptr<GameObjectData>> gameObjects;

    void send(ServerSendProtocol& serverProtocol) override;
};
