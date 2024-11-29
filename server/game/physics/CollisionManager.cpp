#include "CollisionManager.h"

#include <functional>

#include "CollisionObject.h"

CollisionManager::CollisionManager() = default;

void CollisionManager::addCollisionObject(CollisionObject* collisionObject) {
    collisionObjects.push_front(collisionObject);
}

void CollisionManager::removeCollisionObject(CollisionObject* collisionObject) {
    // Since we are using pointers, we can compare memory addresses
    collisionObjects.remove(collisionObject);
}

void CollisionManager::processCollisions(const float delta) const {
    for (CollisionObject* collisionObject: collisionObjects)
        for (const CollisionObject* otherCollisionObject: collisionObjects)
            if (collisionObject != otherCollisionObject)
                collisionObject->registerCollision(
                        otherCollisionObject->getReference<CollisionObject>());

    for (CollisionObject* collisionObject: collisionObjects)
        if (not collisionObject->processCollisions(delta))
            collisionObject->resetRegisteredCollisions();
}
