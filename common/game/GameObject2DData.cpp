#include "GameObject2DData.h"

#include <sstream>

std::string GameObject2DData::_data() {
    auto x = _position.x();
    auto y = _position.y();

    return std::move(std::string(std::move(GameObjectData::_data()))
                             .append(reinterpret_cast<cstring>(&_id), sizeof(u8))
                             .append(reinterpret_cast<cstring>(&x), sizeof(f32))
                             .append(reinterpret_cast<cstring>(&y), sizeof(f32))
                             .append(reinterpret_cast<cstring>(&_rotation), sizeof(f32)));
}

GameObject2DData::GameObject2DData(const GameObject2DData& other) = default;

GameObject2DData& GameObject2DData::operator=(const GameObject2DData& other) = default;

GameObject2DData::GameObject2DData(GameObject2DData&& other) noexcept:
        GameObjectData(std::move(other)),
        _id(other._id),
        _position(std::move(other._position)),
        _rotation(other._rotation) {}

GameObject2DData& GameObject2DData::operator=(GameObject2DData&& other) noexcept {
    GameObjectData::operator=(other);
    _id = other._id;
    _position = std::move(other._position);
    _rotation = other._rotation;
    return *this;
}

GameObject2DData::~GameObject2DData() = default;

GameObject2DData::GameObject2DData(const GameObject2DID id, Vector2 position, const f32 rotation):
        GameObjectData(GameObjectID::OBJECT2D),
        _id(id),
        _position(std::move(position)),
        _rotation(rotation) {}

const Vector2& GameObject2DData::position() const { return _position; }

GameObject2DID GameObject2DData::id2D() const { return _id; }

f32 GameObject2DData::rotation() const { return _rotation; }
