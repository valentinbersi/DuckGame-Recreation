#include "StaticObject.h"

StaticObject::StaticObject(Object* parent, Vector2 position, const float rotation,
                           const std::bitset<LAYERS_COUNT> layers,
                           const std::bitset<LAYERS_COUNT> scannedLayers,
                           std::unique_ptr<Shape2D> shape):
        CollisionObject(parent, std::move(position), rotation, layers, scannedLayers,
                        std::move(shape)) {}

void StaticObject::updateInternal(const float delta) { CollisionObject::updateInternal(delta); }

void StaticObject::registerCollision(
        [[maybe_unused]] std::weak_ptr<CollisionObject> collisionObject) {
    // Left empty on purpose, a static object does nothing with the collisions it registers
}

void StaticObject::processCollisions() {
    // Left empty on purpose, a static object does not process collisions (this may change in the
    // future)
}