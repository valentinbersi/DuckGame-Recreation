#include "GameObjectData.h"

GameObjectData::GameObjectData(const GameObjectData& other) = default;

GameObjectData& GameObjectData::operator=(const GameObjectData& other) = default;

GameObjectData::GameObjectData(GameObjectData&& other) noexcept: _id(other._id) {}

GameObjectData& GameObjectData::operator=(GameObjectData&& other) noexcept {
    _id = other._id;
    return *this;
}

GameObjectData::~GameObjectData() = default;

GameObjectData::GameObjectData(GameObjectID id): _id(id) {}

GameObjectID GameObjectData::id() const { return _id; }