#include "CollisionManager.h"

#include <bits/ranges_algo.h>

#include "CollisionObject.h"

CollisionManager::CollisionManager() = default;

void CollisionManager::addCollisionObject(CollisionObject* collisionObject) {
    collisionObjects.push_front(collisionObject);
}

void CollisionManager::removeCollisionObject(CollisionObject* collisionObject) {
    // Since we are using pointers, we can compare memory addresses
    collisionObjects.remove(collisionObject);
}

void CollisionManager::processCollisions() {
    std::ranges::for_each(collisionObjects, [this](CollisionObject* collisionObject) {
        std::ranges::for_each(
                collisionObjects, [collisionObject](const CollisionObject* otherCollisionObject) {
                    if (collisionObject != otherCollisionObject) {
                        collisionObject->registerCollision(
                                otherCollisionObject->getReference<CollisionObject>());
                    }
                });
    });

    std::ranges::for_each(collisionObjects, [](CollisionObject* collisionObject) {
        collisionObject->processCollisions();
    });
}