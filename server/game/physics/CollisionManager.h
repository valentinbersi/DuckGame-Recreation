#pragma once

#include <forward_list>

class CollisionObject;

class CollisionManager {
    std::forward_list<CollisionObject*> collisionObjects;

public:
    CollisionManager();
    CollisionManager(const CollisionManager&) = delete;
    CollisionManager& operator=(const CollisionManager&) = delete;
    CollisionManager(CollisionManager&&) = delete;
    CollisionManager& operator=(CollisionManager&&) = delete;
    ~CollisionManager() = default;

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
    void processCollisions(float delta) const;
};
