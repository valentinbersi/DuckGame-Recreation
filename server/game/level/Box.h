#pragma once
#include "PhysicsObject.h"
#include "RandomGenerator.h"
#include "SizedObjectData.h"

class Box: public PhysicsObject {
private:
    RandomIntGenerator randomGenerator;
    bool _wasDestroid;

    /**
     * Eliminates the box and generates a random item,
     * an explosion or nothing
     */
    void eliminateBox();

public:
    /**
     * Creates a new box
     * @param position The position of the box
     */
    explicit Box(Vector2 posicion);

    /**
     * Called when the box collides with another object
     * @param object The object that collided with the box
     */
    void onCollision();

    /**
     * Check if the box was destroyed
     * @return true if the box was destroyed
     */
    bool wasDestroyed() const;

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
