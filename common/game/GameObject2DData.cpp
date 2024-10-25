#include "GameObject2DData.h"

GameObject2DData::GameObject2DData(const GameObject2DData& other) = default;

GameObject2DData& GameObject2DData::operator=(const GameObject2DData& other) = default;

GameObject2DData::GameObject2DData(GameObject2DData&& other) noexcept:
        GameObjectData(std::move(other)),
        id(other.id),
        position(std::move(other.position)),
        rotation(other.rotation) {}

GameObject2DData& GameObject2DData::operator=(GameObject2DData&& other) noexcept {
    GameObjectData::operator=(other);
    id = other.id;
    position = std::move(other.position);
    rotation = other.rotation;
    return *this;
}

GameObject2DData::~GameObject2DData() = default;

GameObject2DData::GameObject2DData(const GameObject2DID id, Vector2 position, const float rotation):
        GameObjectData(GameObjectID::Object2D),
        id(id),
        position(std::move(position)),
        rotation(rotation) {}
