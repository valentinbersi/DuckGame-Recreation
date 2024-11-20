#pragma once

#include <memory>
#include <string>

#include "CollisionObject.h"

/**
 * A collision object that throws events when colliding with another collision object
 */
class Area final: public CollisionObject {
protected:
    /**
     * Construct an Area
     * @param parent The parent object
     * @param position The position of the area
     * @param layers The layers of the area
     * @param scannedLayers The layers that the area will scan
     * @param width The width of the area
     * @param height The height of the area
     */
    Area(GameObject* parent, Vector2 position, std::bitset<LayersCount> layers,
         std::bitset<LayersCount> scannedLayers, float width, float height);

public:
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
     * Update the area, does nothing on Area
     * @param delta The time since the last update
     */
    void updateInternal(float delta) override;

    /**
     * Register a collision object to be checked for collisions
     * @param collisionObject The collision object to check for collisions
     */
    void registerCollision(std::weak_ptr<CollisionObject> collisionObject) override;

    /**
     * Process the collisions of the area. This will throw events when colliding with another
     * collision object
     */
    void processCollisions(float delta) override;

    /**
     * The events the Area class has
     */
    enum class Events : u8 { COLLISION };

    /**
     * Get the event name of an event type
     * @param eventType The event type
     * @return The event name
     */
    static std::string eventName(Events eventType);
};
