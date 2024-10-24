#include "GameObjectData.h"

std::string GameObjectData::_data() { return reinterpret_cast<char*>(&_id); }

GameObjectData::GameObjectData(const GameObjectData& other) = default;

GameObjectData& GameObjectData::operator=(const GameObjectData& other) = default;

GameObjectData::GameObjectData(GameObjectData&& other) noexcept: _id(other._id) {}

GameObjectData& GameObjectData::operator=(GameObjectData&& other) noexcept {
    _id = other._id;
    return *this;
}

GameObjectData::~GameObjectData() = default;

GameObjectData::GameObjectData(const GameObjectID id): _id(id) {}

GameObjectID GameObjectData::id() const { return _id; }

std::vector<char> GameObjectData::data() {
    std::string data = _data();
    return {data.begin(), data.end()};
}
