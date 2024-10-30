#include "GameObject2DData.h"

#include <utility>

GameObject2DData::GameObject2DData(const GameObject2DData& other) = default;

GameObject2DData& GameObject2DData::operator=(const GameObject2DData& other) = default;

GameObject2DData::GameObject2DData(GameObject2DData&& other) noexcept:
        GameObjectData(std::move(other)),
        object2DID(other.object2DID),
        position(std::move(other.position)),
        rotation(other.rotation) {}

GameObject2DData& GameObject2DData::operator=(GameObject2DData&& other) noexcept {
    GameObjectData::operator=(other);
    object2DID = other.object2DID;
    position = std::move(other.position);
    rotation = other.rotation;
    return *this;
}

GameObject2DData::~GameObject2DData() = default;

GameObject2DData::GameObject2DData(const GameObject2DID object2DID, Vector2 position,
                                   const float rotation):
        GameObjectData(GameObjectID::Object2D),
        object2DID(object2DID),
        position(std::move(position)),
        rotation(rotation) {}
