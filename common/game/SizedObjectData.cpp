#include "SizedObjectData.h"

SizedObjectData::SizedObjectData(const SizedObjectData& other) = default;

SizedObjectData& SizedObjectData::operator=(const SizedObjectData& other) {
    if (this == &other)
        return *this;

    GameObject2DData::operator=(other);
    rectangle = other.rectangle;
    return *this;
}

SizedObjectData::SizedObjectData(SizedObjectData&& other) noexcept: GameObject2DData(std::move(other)), rectangle(std::move(other.rectangle)) {}

SizedObjectData& SizedObjectData::operator=(SizedObjectData&& other) noexcept {
    if (this == &other)
        return *this;

    GameObject2DData::operator=(std::move(other));
    rectangle = std::move(other.rectangle);
    return *this;
}

SizedObjectData::~SizedObjectData() = default;

SizedObjectData::SizedObjectData(const Vector2& position, float width, float height): GameObject2DData(position), rectangle(position, width, height) {}

