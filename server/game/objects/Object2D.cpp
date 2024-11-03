#include "Object2D.h"

#include <utility>

Object2D::Object2D(Object* parent, Vector2 position, const float rotation):
        Object(parent), _position(std::move(position)), _rotation(rotation) {}

Object2D::Object2D(const Object2D& other) = default;

Object2D& Object2D::operator=(const Object2D& other) {
    if (this == &other)
        return *this;

    Object::operator=(other);
    _position = other._position;
    _rotation = other._rotation;
    return *this;
}

Object2D::Object2D(Object2D&& other) noexcept:
        Object(std::move(other)),
        _position(std::move(other._position)),
        _rotation(other._rotation) {}

Object2D& Object2D::operator=(Object2D&& other) noexcept {
    if (this == &other)
        return *this;

    Object::operator=(std::move(other));
    _position = std::move(other._position);
    _rotation = other._rotation;
    return *this;
}

Object2D::~Object2D() = default;

Object2D& Object2D::globalPosition(Vector2 globalPosition) noexcept try {
    const auto& parent2D = dynamic_cast<Object2D&>(parent());

    _position = globalPosition - parent2D.globalPosition();
    return *this;

} catch (std::bad_cast&) {
    _position = std::move(globalPosition);
    return *this;
}

Vector2 Object2D::globalPosition() const noexcept try {
    const auto& parent2D = dynamic_cast<Object2D&>(parent());

    if (_position == Vector2::ZERO)
        return parent2D.globalPosition();

    return parent2D.globalPosition() +
           Vector2::RIGHT.rotated(parent2D.globalRotation()) * position.length();

} catch (std::bad_cast&) {
    return _position;
}

Object2D& Object2D::globalRotation(const float globalRotation) noexcept try {
    const auto& parent2D = dynamic_cast<Object2D&>(parent());

    _rotation = globalRotation - parent2D.globalRotation();
    return *this;
} catch (std::bad_cast&) {
    _rotation = globalRotation;
    return *this;
}

float Object2D::globalRotation() const noexcept try {
    const auto& parent2D = dynamic_cast<Object2D&>(parent());

    if (_position == Vector2::ZERO)
        return parent2D.globalRotation();

    return _rotation + parent2D.globalRotation();
} catch (std::bad_cast&) {
    return _rotation;
}

Object2D& Object2D::position(Vector2 position) noexcept {
    _position = std::move(position);
    return *this;
}

const Vector2& Object2D::position() const noexcept { return _position; }

Object2D& Object2D::rotation(const float rotation) noexcept {
    _rotation = rotation;
    return *this;
}

float Object2D::rotation() const noexcept { return _rotation; }
