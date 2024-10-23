#pragma once

#include "GameObjectData.h"

/**
 * A struct with the current game status.
 */
class GameStatus {
    std::vector<std::unique_ptr<GameObjectData>> _gameObjects;

public:
    GameStatus();
    GameStatus(const GameStatus& other) = delete;
    GameStatus& operator=(const GameStatus& other) = delete;
    GameStatus(GameStatus&& other) noexcept;
    GameStatus& operator=(GameStatus&& other) noexcept;

    /**
     * Add a game object to the game status.
     * @param gameObject The game object to add.
     * @return The game status.
     */
    GameStatus& addObject(std::unique_ptr<GameObjectData> gameObject);

    /**
     * Get the game objects.
     * @return The game objects.
     */
    [[nodiscard]] const std::vector<std::unique_ptr<GameObjectData>>& gameObjects() const;
};
