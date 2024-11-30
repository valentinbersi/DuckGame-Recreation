#include "GameObject2D.h"

#include <utility>

GameObject2D::~GameObject2D() = default;

GameObject2D::GameObject2D(Vector2 position):
        _globalPosition(std::move(position)), _position(_globalPosition) {}

void GameObject2D::updateInternal([[maybe_unused]] const float delta) {
    if (const auto parent2D = dynamic_cast<const GameObject2D*>(parent()); parent2D != nullptr)
        _globalPosition = parent2D->_globalPosition + _position;

    GameObject::updateInternal(delta);
}

GameObject2D& GameObject2D::setGlobalPosition(Vector2 globalPosition,
                                              [[maybe_unused]] const Force force) noexcept {
    _globalPosition = std::move(globalPosition);

    const auto parent2D = dynamic_cast<const GameObject2D*>(parent());

    if (parent2D == nullptr) {
        _position = _globalPosition;
        return *this;
    }

    _position = _globalPosition - parent2D->_globalPosition;
    return *this;
}

const Vector2& GameObject2D::globalPosition() const noexcept { return _globalPosition; }

GameObject2D& GameObject2D::setPosition(Vector2 position,
                                        [[maybe_unused]] const Force force) noexcept {
    _position = std::move(position);

    const auto parent2D = dynamic_cast<const GameObject2D*>(parent());

    if (parent2D == nullptr) {
        _globalPosition = _position;
        return *this;
    }

    _globalPosition = _position + parent2D->globalPosition();
    return *this;
}

const Vector2& GameObject2D::position() const noexcept { return _position; }
