#include "GameStatus.hpp"

GameStatus::GameStatus(const std::initializer_list<std::unique_ptr<GameObjectData>> objects):
        _gameObjects(objects) {}

const std::vector<std::unique_ptr<GameObjectData>>& GameStatus::gameObjects() const {
    return _gameObjects;
}