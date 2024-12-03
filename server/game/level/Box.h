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
     * Checks if it was destroyed and eliminates the box
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
