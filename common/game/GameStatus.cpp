#include "GameStatus.hpp"

#include <utility>

GameStatus::GameStatus() = default;

GameStatus::GameStatus(GameStatus&& other) noexcept: gameObjects(std::move(other.gameObjects)) {}

GameStatus& GameStatus::operator=(GameStatus&& other) noexcept {
    if (this == &other)
        return *this;

    gameObjects = std::move(other.gameObjects);
    return *this;
}
