#include "StaticObject.h"

void StaticObject::updateInternal(const float delta) { CollisionObject::updateInternal(delta); }

void StaticObject::registerCollision(
        [[maybe_unused]] std::weak_ptr<CollisionObject> collisionObject) {
    // Left empty on purpose, a static object does nothing with the collisions it registers
}

void StaticObject::processCollisions() {
    // Left empty on purpose, a static object does not process collisions (this may change in the
    // future)
}