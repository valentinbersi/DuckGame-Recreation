#pragma once

#include "CollisionObject.h"

/**
 * A collision object that throws events when colliding with another collision object
 */
struct Area: CollisionObject {
    /**
     * Construct an Area
     * @param position The position of the area
     * @param layers The layers of the area
     * @param scannedLayers The layers that the area will scan
     * @param width The width of the area
     * @param height The height of the area
     */
    Area(const Vector2& position, std::bitset<LayersCount> layers,
         std::bitset<LayersCount> scannedLayers, float width, float height);

    Area() = delete;
    Area(const Area&) = delete;
    Area& operator=(const Area&) = delete;
    Area(Area&&) = delete;
    Area& operator=(Area&&) = delete;
    ~Area() override = default;

    /**
     * Does nothing on area
     */
    void start() override;

    /**
     * Does nothing on Area
     */
    void update(float delta) override;

    /**
     * Process the collisions of the area. This will throw events when colliding with another
     * collision object
     */
    bool processCollisions(float delta) override;
};
