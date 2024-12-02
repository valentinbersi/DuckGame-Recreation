#pragma once
#include "PhysicsObject.h"
#include "RandomGenerator.h"
#include "SizedObjectData.h"

class Box: public PhysicsObject {
private:
    RandomIntGenerator randomGenerator;
    bool wasDestroid;

    /**
     * Eliminates the box and generates a random item,
     * an explosion or nothing
     */
    void eliminateBox();

    /**
     * Called when the box collides with another object
     */
    void onCollision(const CollisionObject* object);

public:
    /**
     * Creates a new box
     * @param position The position of the box
     */
    explicit Box(Vector2 posicion);

    /**
     * Check if the box was destroyed on the last frame
     * @param delta The time since the last update
     */
    void update(float delta) override;

    /**
     * Get the position of the box and its dimensions
     * @return ]the sizedObjectData of the box
     */
    SizedObjectData status() const;

    /**
     * Destroys the box
     */
    ~Box() override;
};
