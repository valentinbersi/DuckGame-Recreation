#include "GameObjectData.h"

GameObjectData::GameObjectData(const GameObjectData& other) = default;

GameObjectData& GameObjectData::operator=(const GameObjectData& other) = default;

GameObjectData::GameObjectData(GameObjectData&& other) noexcept: objectID(other.objectID) {}

GameObjectData& GameObjectData::operator=(GameObjectData&& other) noexcept {
    objectID = other.objectID;
    return *this;
}

GameObjectData::~GameObjectData() = default;

GameObjectData::GameObjectData(const GameObjectID objectID): objectID(objectID) {}
