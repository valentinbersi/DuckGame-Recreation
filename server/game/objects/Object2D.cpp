#include "Object2D.h"

#include <utility>

Object2D::Object2D(Object* parent): Object2D(parent, {0, 0}, 0) {}

Object2D::Object2D(Object* parent, Vector2 position, const float rotation): Object(parent) {
    _position = std::move(position);
    _rotation = rotation;

    const auto parent2D = dynamic_cast<Object2D*>(parent);

    if (parent2D == nullptr) {
        _globalPosition = _position;
        _globalRotation = _rotation;
        return;
    }

    if (position == Vector2::ZERO) {
        _globalPosition = _position + parent2D->_globalPosition;
        _globalRotation = _rotation + parent2D->_globalRotation;
        return;
    }

    _globalPosition = parent2D->_globalPosition +
                      Vector2::RIGHT.rotated(parent2D->_globalRotation) * position.length();

    _globalRotation = _rotation + parent2D->_globalRotation;
}

Object2D::Object2D(): Object2D(nullptr) {}

Object2D::Object2D(const Object2D& other) = default;

Object2D& Object2D::operator=(const Object2D& other) {
    if (this == &other)
        return *this;

    Object::operator=(other);
    _globalPosition = other._globalPosition;
    _globalRotation = other._globalRotation;
    _position = other._position;
    _rotation = other._rotation;
    return *this;
}

Object2D::Object2D(Object2D&& other) noexcept:
        Object(std::move(other)),
        _globalPosition(std::move(other._globalPosition)),
        _globalRotation(other._globalRotation),
        _position(std::move(other._position)),
        _rotation(other._rotation) {}

Object2D& Object2D::operator=(Object2D&& other) noexcept {
    if (this == &other)
        return *this;

    Object::operator=(std::move(other));
    _globalPosition = std::move(other._globalPosition);
    _globalRotation = other._globalRotation;
    _position = std::move(other._position);
    _rotation = other._rotation;
    return *this;
}

Object2D::Object2D(Vector2 position, const float rotation):
        Object2D(nullptr, std::move(position), rotation) {}

Object2D& Object2D::globalPosition(Vector2 globalPosition) noexcept {
    _globalPosition = std::move(globalPosition);

    const auto parent2D = dynamic_cast<Object2D*>(parent());

    if (parent2D == nullptr) {
        _position = _globalPosition;
        return *this;
    }

    _position = _globalPosition - parent2D->_globalPosition;
    return *this;
}

const Vector2& Object2D::globalPosition() const noexcept { return _globalPosition; }

Object2D& Object2D::globalRotation(const float globalRotation) noexcept {
    _globalRotation = globalRotation;

    const auto parent2D = dynamic_cast<Object2D*>(parent());

    if (parent2D == nullptr) {
        _rotation = _globalRotation;
        return *this;
    }

    _rotation = _globalRotation - parent2D->_globalRotation;
    return *this;
}

float Object2D::globalRotation() const noexcept { return _globalRotation; }

Object2D& Object2D::position(Vector2 position) noexcept {
    _position = std::move(position);

    const auto parent2D = dynamic_cast<Object2D*>(parent());

    if (parent2D == nullptr) {
        _globalPosition = _position;
        return *this;
    }

    _globalPosition = _position + parent2D->_globalPosition;
    return *this;
}

const Vector2& Object2D::position() const noexcept { return _position; }

Object2D& Object2D::rotation(const float rotation) noexcept {
    _rotation = rotation;

    const auto parent2D = dynamic_cast<Object2D*>(parent());

    if (parent2D == nullptr) {
        _globalRotation = _rotation;
        return *this;
    }

    _globalRotation = _rotation + parent2D->_globalRotation;
    return *this;
}

float Object2D::rotation() const noexcept { return _rotation; }
