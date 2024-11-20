#include "GameObject2DData.h"

#include <utility>

GameObject2DData::GameObject2DData(const GameObject2DData& other) = default;

GameObject2DData& GameObject2DData::operator=(const GameObject2DData& other) {
    if (this == &other)
        return *this;

    position = other.position;
    return *this;
}

GameObject2DData::GameObject2DData(GameObject2DData&& other) noexcept:
        position(std::move(other.position)) {}

GameObject2DData& GameObject2DData::operator=(GameObject2DData&& other) noexcept {
    if (this == &other)
        return *this;

    position = std::move(other.position);
    return *this;
}

GameObject2DData::~GameObject2DData() = default;

GameObject2DData::GameObject2DData(Vector2 position): position(std::move(position)) {}
