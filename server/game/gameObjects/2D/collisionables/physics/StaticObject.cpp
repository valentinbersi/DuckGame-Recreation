#include "StaticObject.h"

#include <utility>

StaticObject::StaticObject(Vector2 position, const std::bitset<LayersCount> layers,
                           const std::bitset<LayersCount> scannedLayers, const float width,
                           const float height):
        CollisionObject(std::move(position), layers, scannedLayers, width, height) {}

void StaticObject::updateInternal(const float delta) { CollisionObject::updateInternal(delta); }

void StaticObject::registerCollision(
        [[maybe_unused]] std::weak_ptr<CollisionObject> collisionObject) {}

void StaticObject::processCollisions([[maybe_unused]] const float delta) {}
