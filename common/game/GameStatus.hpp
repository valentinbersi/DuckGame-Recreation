#pragma once
#include "ObjectData.h"

/**
 * A struct with the current game status.
 */
class GameStatus {
    std::vector<std::unique_ptr<ObjectData>> _gameObjects;
    // Time matchTime

public:
    GameStatus(std::initializer_list<std::unique_ptr<ObjectData>> objects /*, Time matchTime*/);

    [[nodiscard]] const std::vector<std::unique_ptr<ObjectData>>& gameObjects() const;

    // [[nodiscard]] Time matchTime() const;
};
