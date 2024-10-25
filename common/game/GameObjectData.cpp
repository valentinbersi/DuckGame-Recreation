#include "GameObjectData.h"

GameObjectData::GameObjectData(const GameObjectData& other) = default;

GameObjectData& GameObjectData::operator=(const GameObjectData& other) = default;

GameObjectData::GameObjectData(GameObjectData&& other) noexcept: id(other.id) {}

GameObjectData& GameObjectData::operator=(GameObjectData&& other) noexcept {
    id = other.id;
    return *this;
}

GameObjectData::~GameObjectData() = default;

GameObjectData::GameObjectData(const GameObjectID id): id(id) {}
