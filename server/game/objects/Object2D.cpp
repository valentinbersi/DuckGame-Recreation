#include "Object2D.h"

Object2D::Object2D(Object2D* parent): Object2D(parent, {0, 0}, 0, {1, 1}) {}

Object2D::Object2D(Object* parent, Vector2 position, const float rotation, Vector2 scale):
        Object(parent),
        _globalPosition(position),
        _globalRotation(rotation),
        _globalScale(scale),
        _position(std::move(position)),
        _rotation(rotation),
        _scale(std::move(scale)) {

    if (const auto parent2D = dynamic_cast<Object2D*>(parent); parent2D != nullptr) {
        _globalPosition += parent2D->_globalPosition;
        _globalRotation += parent2D->_globalRotation;
        _globalScale += parent2D->_globalScale;
        return;
    }
}

Object2D::Object2D(): Object2D(nullptr) {}

Object2D::Object2D(const Object2D& other) = default;

Object2D& Object2D::operator=(const Object2D& other) {
    if (this == &other)
        return *this;

    Object::operator=(other);
    _globalPosition = other._globalPosition;
    _globalRotation = other._globalRotation;
    _globalScale = other._globalScale;
    _position = other._position;
    _rotation = other._rotation;
    _scale = other._scale;
    return *this;
}

Object2D::Object2D(Object2D&& other) noexcept: Object(std::move(other)) {
    _globalPosition = std::move(other._globalPosition);
    _globalRotation = other._globalRotation;
    _globalScale = std::move(other._globalScale);
    _position = std::move(other._position);
    _rotation = other._rotation;
    _scale = std::move(other._scale);
}

Object2D& Object2D::operator=(Object2D&& other) noexcept {
    if (this == &other)
        return *this;

    Object::operator=(std::move(other));
    _globalPosition = std::move(other._globalPosition);
    _globalRotation = other._globalRotation;
    _globalScale = std::move(other._globalScale);
    _position = std::move(other._position);
    _rotation = other._rotation;
    _scale = std::move(other._scale);
    return *this;
}

Object2D::Object2D(Vector2 position, const float rotation, Vector2 scale):
        Object2D(nullptr, std::move(position), rotation, std::move(scale)) {}

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

Object2D& Object2D::globalScale(Vector2 globalScale) noexcept {
    _globalScale = std::move(globalScale);

    const auto parent2D = dynamic_cast<Object2D*>(parent());

    if (parent2D == nullptr) {
        _scale = _globalScale;
        return *this;
    }

    _scale = _globalScale - parent2D->_globalScale;
    return *this;
}

const Vector2& Object2D::globalScale() const noexcept { return _globalScale; }

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

Object2D& Object2D::scale(Vector2 scale) noexcept {
    _scale = std::move(scale);

    const auto parent2D = dynamic_cast<Object2D*>(parent());

    if (parent2D == nullptr) {
        _globalScale = _scale;
        return *this;
    }

    _globalScale = _scale + parent2D->_globalScale;
    return *this;
}

const Vector2& Object2D::scale() const noexcept { return _scale; }
