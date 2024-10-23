#pragma once
#include "GameObjectData.h"

/**
 * A struct with the current game status.
 */
class GameStatus {
    std::vector<std::unique_ptr<GameObjectData>> _gameObjects;
    // Time matchTime

public:
    GameStatus(std::initializer_list<std::unique_ptr<GameObjectData>> objects /*, Time matchTime*/);

    [[nodiscard]] const std::vector<std::unique_ptr<GameObjectData>>& gameObjects() const;

    // [[nodiscard]] Time matchTime() const;
};
