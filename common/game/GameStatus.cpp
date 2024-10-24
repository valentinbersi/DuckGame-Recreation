#include "GameStatus.hpp"

GameStatus::GameStatus() = default;

GameStatus::GameStatus(GameStatus&& other) noexcept: _gameObjects(std::move(other._gameObjects)) {}

GameStatus& GameStatus::operator=(GameStatus&& other) noexcept {
    if (this == &other)
        return *this;

    _gameObjects = std::move(other._gameObjects);
    return *this;
}

GameStatus& GameStatus::addObject(std::unique_ptr<GameObjectData> gameObject) {
    _gameObjects.push_back(std::move(gameObject));
    return *this;
}

const std::vector<std::unique_ptr<GameObjectData>>& GameStatus::gameObjects() const {
    return _gameObjects;
}