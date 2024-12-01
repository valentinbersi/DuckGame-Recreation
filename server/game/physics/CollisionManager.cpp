#include "CollisionManager.h"

#include <functional>

#include "CollisionObject.h"
#include "RayCast.h"

CollisionManager::CollisionManager() = default;

void CollisionManager::addRayCast(RayCast* rayCast) { rayCasts.push_front(rayCast); }

void CollisionManager::removeRayCast(RayCast* rayCast) {
    // Since we are using pointers, we can compare memory addresses
    rayCasts.remove(rayCast);
}

void CollisionManager::addCollisionObject(CollisionObject* collisionObject) {
    collisionObjects.push_front(collisionObject);
}

void CollisionManager::removeCollisionObject(CollisionObject* collisionObject) {
    // Since we are using pointers, we can compare memory addresses
    collisionObjects.remove(collisionObject);
}

void CollisionManager::processCollisions(const float delta) const {
    for (RayCast* rayCast: rayCasts)
        for (const CollisionObject* collisionObject: collisionObjects)
            rayCast->registerCollisions(collisionObject->getReference<CollisionObject>());

    for (RayCast* rayCast: rayCasts) {
        rayCast->processCollisions();
        rayCast->clearCollisions();
    }

    for (CollisionObject* collisionObject: collisionObjects)
        for (const CollisionObject* otherCollisionObject: collisionObjects)
            if (collisionObject != otherCollisionObject)
                collisionObject->registerCollision(
                        otherCollisionObject->getReference<CollisionObject>());

    for (CollisionObject* collisionObject: collisionObjects)
        if (not collisionObject->processCollisions(delta))
            collisionObject->resetRegisteredCollisions();
}
