#include "GameObject2DData.h"

GameObject2DData::GameObject2DData(const GameObject2DData& other) = default;

GameObject2DData& GameObject2DData::operator=(const GameObject2DData& other) = default;

GameObject2DData::GameObject2DData(GameObject2DData&& other) noexcept:
        GameObjectData(std::move(other)),
        _position(std::move(other._position)),
        _rotation(other._rotation) {}

GameObject2DData& GameObject2DData::operator=(GameObject2DData&& other) noexcept {
    GameObjectData::operator=(other);
    _position = std::move(other._position);
    _rotation = other._rotation;
    return *this;
}

GameObject2DData::~GameObject2DData() = default;

GameObject2DData::GameObject2DData(const GameObjectID id, Vector2 position, const f32 rotation):
        GameObjectData(id), _position(std::move(position)), _rotation(rotation) {}

const Vector2& GameObject2DData::position() const { return _position; }

f32 GameObject2DData::rotation() const { return _rotation; }