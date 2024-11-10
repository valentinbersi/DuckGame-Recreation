#include "Object2D.h"

#include <utility>

Object2D::Object2D(Object* parent, Vector2 position, const float rotation):
        Object(parent), _position(std::move(position)), _rotation(rotation) {

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

Object2D::~Object2D() = default;

void Object2D::updateInternal([[maybe_unused]] const float delta) {
    if (const auto parent2D = dynamic_cast<Object2D*>(parent()); parent2D != nullptr) {
        if (_position == Vector2::ZERO)
            _globalPosition = parent2D->_globalPosition;
        else
            _globalPosition =
                    parent2D->_globalPosition +
                    Vector2::RIGHT.rotated(parent2D->_globalRotation) * _position.length();

        _globalRotation = _rotation + parent2D->_globalRotation;
    }

    Object::updateInternal(delta);
}

Object2D& Object2D::setGlobalPosition(Vector2 globalPosition) noexcept {
    _globalPosition = std::move(globalPosition);

    const auto parent2D = dynamic_cast<Object2D*>(parent());

    if (parent2D == nullptr) {
        _position = _globalPosition;
        return *this;
    }

    _position = (_globalPosition - parent2D->_globalPosition).rotated(-parent2D->globalRotation());
    return *this;
}

const Vector2& Object2D::globalPosition() const noexcept { return _globalPosition; }

Object2D& Object2D::setGlobalRotation(const float globalRotation) noexcept {
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

Object2D& Object2D::setPosition(Vector2 position) noexcept {
    _position = std::move(position);

    const auto parent2D = dynamic_cast<Object2D*>(parent());

    if (parent2D == nullptr) {
        _globalPosition = _position;
        return *this;
    }

    if (_position == Vector2::ZERO)
        _globalPosition = _position;
    else
        _globalPosition = parent2D->_globalPosition +
                          Vector2::RIGHT.rotated(parent2D->_globalRotation) * position.length();
    return *this;
}

const Vector2& Object2D::position() const noexcept { return _position; }

Object2D& Object2D::setRotation(const float rotation) noexcept {
    _rotation = rotation;

    const auto& parent2D = dynamic_cast<Object2D*>(parent());

    if (parent2D == nullptr) {
        _globalRotation = _rotation;
        return *this;
    }

    _globalRotation = _rotation + parent2D->_globalRotation;
    return *this;
}

float Object2D::rotation() const noexcept { return _rotation; }
