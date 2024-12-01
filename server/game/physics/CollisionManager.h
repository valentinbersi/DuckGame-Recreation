#pragma once

#include <forward_list>


class RayCast;
class CollisionObject;

class CollisionManager {
    std::forward_list<RayCast*> rayCasts;
    std::forward_list<CollisionObject*> collisionObjects;
    std::forward_list<CollisionObject*> toRemove;

public:
    CollisionManager();
    CollisionManager(const CollisionManager&) = delete;
    CollisionManager& operator=(const CollisionManager&) = delete;
    CollisionManager(CollisionManager&&) = delete;
    CollisionManager& operator=(CollisionManager&&) = delete;
    ~CollisionManager() = default;

    /**
     * Add a rayCast to the list of rayCasts
     * @param rayCast The rayCast to add
     */
    void addRayCast(RayCast* rayCast);

    /**
     * Remove a rayCast from the list of rayCasts
     * @param rayCast The rayCast to remove
     */
    void removeRayCast(RayCast* rayCast);

    /**
     * Add a collisionObject to the list of collisionObjects
     * @param collisionObject The collisionObject to add
     */
    void addCollisionObject(CollisionObject* collisionObject);

    /**
     * Remove a collisionObject from the list of collisionObjects
     * @param collisionObject The collisionObject to remove
     */
    void removeCollisionObject(CollisionObject* collisionObject);

    /**
     * Process all collisions between collisionObjects
     * @param delta The time since the last frame
     */
    void processCollisions(float delta);
};
