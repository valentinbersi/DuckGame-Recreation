#include "GameObject2D.h"

#include <utility>

GameObject2D::GameObject2D(GameObject* parent, Vector2 position, const float rotation):
        GameObject(parent), _position(std::move(position)), _rotation(rotation) {

    const auto parent2D = dynamic_cast<GameObject2D*>(parent);

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

GameObject2D::~GameObject2D() = default;

void GameObject2D::updateInternal([[maybe_unused]] const float delta) {
    if (const auto parent2D = dynamic_cast<GameObject2D*>(parent()); parent2D != nullptr) {
        if (_position == Vector2::ZERO)
            _globalPosition = parent2D->_globalPosition;
        else
            _globalPosition =
                    parent2D->_globalPosition +
                    Vector2::RIGHT.rotated(parent2D->_globalRotation) * _position.length();

        _globalRotation = _rotation + parent2D->_globalRotation;
    }

    GameObject::updateInternal(delta);
}

GameObject2D& GameObject2D::setGlobalPosition(Vector2 globalPosition) noexcept {
    _globalPosition = std::move(globalPosition);

    const auto parent2D = dynamic_cast<GameObject2D*>(parent());

    if (parent2D == nullptr) {
        _position = _globalPosition;
        return *this;
    }

    _position = (_globalPosition - parent2D->_globalPosition).rotated(-parent2D->globalRotation());
    return *this;
}

const Vector2& GameObject2D::globalPosition() const noexcept { return _globalPosition; }

GameObject2D& GameObject2D::setGlobalRotation(const float globalRotation) noexcept {
    _globalRotation = globalRotation;

    const auto parent2D = dynamic_cast<GameObject2D*>(parent());

    if (parent2D == nullptr) {
        _rotation = _globalRotation;
        return *this;
    }

    _rotation = _globalRotation - parent2D->_globalRotation;
    return *this;
}

float GameObject2D::globalRotation() const noexcept { return _globalRotation; }

GameObject2D& GameObject2D::setPosition(Vector2 position) noexcept {
    _position = std::move(position);

    const auto parent2D = dynamic_cast<GameObject2D*>(parent());

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

const Vector2& GameObject2D::position() const noexcept { return _position; }

GameObject2D& GameObject2D::setRotation(const float rotation) noexcept {
    _rotation = rotation;

    const auto& parent2D = dynamic_cast<GameObject2D*>(parent());

    if (parent2D == nullptr) {
        _globalRotation = _rotation;
        return *this;
    }

    _globalRotation = _rotation + parent2D->_globalRotation;
    return *this;
}

float GameObject2D::rotation() const noexcept { return _rotation; }
