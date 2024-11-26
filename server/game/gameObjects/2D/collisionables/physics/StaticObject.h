#pragma once

#include <memory>

#include "CollisionObject.h"

/**
 * A collision Object that physics do not affect.\n
 * It's intended for creating objects not affected by physics that physics object can collide with
 */
struct StaticObject: CollisionObject {
    StaticObject() = delete;
    StaticObject(const StaticObject&) = delete;
    StaticObject& operator=(const StaticObject&) = delete;
    StaticObject(StaticObject&&) = delete;
    StaticObject& operator=(StaticObject&&) = delete;

    /**
     * Creates a new static object
     * @param position The position of the object
     * @param layers The layers the object is in
     * @param scannedLayers The layers the object scans for collisions
     * @param width The width
     * @param height The height
     */
    StaticObject(Vector2 position, std::bitset<LayersCount> layers,
                 std::bitset<LayersCount> scannedLayers, float width, float height);

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
    void processCollisions(float delta) final;
};
