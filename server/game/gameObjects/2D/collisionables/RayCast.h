#pragma once

#include <bitset>
#include <forward_list>
#include <memory>

#include "CollisionObject.h"
#include "GameObject.h"
#include "Segment2D.h"

class RayCast final: public GameObject {
    constexpr static u8 LayersCount = 32;

    Segment2D ray;
    std::bitset<LayersCount> scannedLayers;
    std::forward_list<std::weak_ptr<CollisionObject>> objectsToCollide;

public:
    /**
     * Construct a RayCast object with a start and end point
     * @param start The start point of the ray
     * @param end The end point of the ray
     * @param scannedLayers The layers to scan for collisions
     */
    RayCast(Vector2 start, Vector2 end, std::bitset<LayersCount> scannedLayers);

    /**
     * Register objects to detect collision with
     * @param object The object to detect collision with
     */
    void registerCollisions(std::weak_ptr<CollisionObject> object);

    /**
     * Process the collisions with the registered objects and fire the collision event only for the
     * closest collision
     */
    void processCollisions();

    /**
     * Clear the collisions
     */
    void clearCollisions();

    struct Events {
        constexpr static auto Collision = "Collision";
    };
};
