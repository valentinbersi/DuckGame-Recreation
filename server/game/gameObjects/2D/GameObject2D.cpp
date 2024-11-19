#include "GameObject2D.h"

#include <utility>

GameObject2D::GameObject2D(GameObject* parent, Vector2 position):
        GameObject(parent), _position(std::move(position)) {

    const auto parent2D = dynamic_cast<GameObject2D*>(parent);

    if (parent2D == nullptr) {
        _globalPosition = _position;
        return;
    }

    _globalPosition = _position + parent2D->_globalPosition;
}

GameObject2D::~GameObject2D() = default;

void GameObject2D::updateInternal([[maybe_unused]] const float delta) {
    if (const auto parent2D = dynamic_cast<GameObject2D*>(parent()); parent2D != nullptr)
        _globalPosition = parent2D->_globalPosition;

    GameObject::updateInternal(delta);
}

GameObject2D& GameObject2D::setGlobalPosition(Vector2 globalPosition) noexcept {
    _globalPosition = std::move(globalPosition);

    const auto parent2D = dynamic_cast<GameObject2D*>(parent());

    if (parent2D == nullptr) {
        _position = _globalPosition;
        return *this;
    }

    _position = _globalPosition - parent2D->_globalPosition;
    return *this;
}

const Vector2& GameObject2D::globalPosition() const noexcept { return _globalPosition; }

GameObject2D& GameObject2D::setPosition(Vector2 position) noexcept {
    _position = std::move(position);

    const auto parent2D = dynamic_cast<GameObject2D*>(parent());

    if (parent2D == nullptr) {
        _globalPosition = _position;
        return *this;
    }

    _globalPosition = _position + parent2D->globalPosition();
    return *this;
}

const Vector2& GameObject2D::position() const noexcept { return _position; }
