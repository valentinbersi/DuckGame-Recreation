#include "GameStatus.hpp"

GameStatus::GameStatus() = default;

GameStatus::GameStatus(GameStatus&& other) noexcept: _gameObjects(std::move(other._gameObjects)) {}

GameStatus& GameStatus::operator=(GameStatus&& other) noexcept {
    if (this == &other)
        return *this;

    _gameObjects = std::move(other._gameObjects);
    return *this;
}
