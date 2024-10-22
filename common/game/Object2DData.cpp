#include "Object2DData.h"

Object2DData::Object2DData(const Object2DData& other) = default;

Object2DData& Object2DData::operator=(const Object2DData& other) = default;

Object2DData::Object2DData(Object2DData&& other) noexcept:
        ObjectData(std::move(other)),
        _position(std::move(other._position)),
        _rotation(other._rotation) {}

Object2DData& Object2DData::operator=(Object2DData&& other) noexcept {
    ObjectData::operator=(other);
    _position = std::move(other._position);
    _rotation = other._rotation;
    return *this;
}

Object2DData::~Object2DData() = default;

Object2DData::Object2DData(const u32 id, Vector2 position, const f32 rotation):
        ObjectData(id), _position(std::move(position)), _rotation(rotation) {}

const Vector2& Object2DData::position() const { return _position; }

f32 Object2DData::rotation() const { return _rotation; }