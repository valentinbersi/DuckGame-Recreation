#include "StaticObject.h"

#include <memory>
#include <utility>

StaticObject::StaticObject(GameObject* parent, Vector2 position,
                           const std::bitset<LayersCount> layers,
                           const std::bitset<LayersCount> scannedLayers, const float width,
                           const float height):
        CollisionObject(parent, std::move(position), layers, scannedLayers, width, height) {}

void StaticObject::updateInternal(const float delta) { CollisionObject::updateInternal(delta); }

void StaticObject::registerCollision(
        [[maybe_unused]] std::weak_ptr<CollisionObject> collisionObject) {
    // Left empty on purpose, a static object does nothing with the collisions it registers
}

void StaticObject::processCollisions([[maybe_unused]] const float delta) {
    // Left empty on purpose, a static object does not process collisions (this may change in the
    // future)
}
