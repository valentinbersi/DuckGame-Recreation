#pragma once

#include "CollisionObject.h"

/**
 * A collision Object that physics do not affect.\n
 * It's intended for creating objects not affected by physics that physics object can collide with
 */
class StaticObject: public CollisionObject {
public:
    StaticObject() = delete;
    StaticObject(const StaticObject&) = delete;
    StaticObject& operator=(const StaticObject&) = delete;
    StaticObject(StaticObject&&) = delete;
    StaticObject& operator=(StaticObject&&) = delete;

    /**
     * Update the object's internal state
     * @param delta Time since the last update
     */
    void updateInternal(float delta) final;

    /**
     * Does nothing on StaticObject
     */
    void registerCollision(std::weak_ptr<CollisionObject> collisionObject) final;

    /**
     * Does nothing on StaticObject
     */
    void processCollisions() final;
};
