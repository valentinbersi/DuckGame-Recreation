#pragma once

#include <list>
#include <memory>

#include "GameObjectData.h"

/**
 * A struct with the current game status.
 */
struct GameStatus {
    GameStatus();
    GameStatus(const GameStatus& other) = delete;
    GameStatus& operator=(const GameStatus& other) = delete;
    GameStatus(GameStatus&& other) noexcept;
    GameStatus& operator=(GameStatus&& other) noexcept;

    std::list<std::unique_ptr<GameObjectData>> gameObjects;
};
