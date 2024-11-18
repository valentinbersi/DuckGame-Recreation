#pragma once

#include "CollisionObject.h"
#include "Vector2.h"

class PhysicsObject: public CollisionObject {
public:
    enum class Gravity : u8 { Enabled, Disabled };

private:
    Vector2 _velocity;
    Gravity gravity;

protected:
    /**
     * Creates a new physics object
     * @param parent The parent object
     * @param position The position of the object
     * @param layers The layer the object is in
     * @param scannedLayers The layer the object scans for collisions
     * @param width The width of the object
     * @param height The height of the object
     * @param initialVelocity The initial velocity of the object
     * @param gravity the gravity configuration for this object
     */
    PhysicsObject(GameObject* parent, Vector2 position, std::bitset<LayersCount> layers,
                  std::bitset<LayersCount> scannedLayers, float width, float height,
                  Vector2 initialVelocity, Gravity gravity);

public:
    PhysicsObject() = delete;
    PhysicsObject(const PhysicsObject& other) = delete;
    PhysicsObject& operator=(const PhysicsObject& other) = delete;
    PhysicsObject(PhysicsObject&& other) noexcept = delete;
    PhysicsObject& operator=(PhysicsObject&& other) noexcept = delete;
    ~PhysicsObject() override;

    /**
     * Apply gravity to the object
     * @param delta The time since the last update
     */
    void updateInternal(float delta) final;

    /**
     * Calculate the new position of the object based on its velocity.
     * @param delta The time since the last update
     */
    void processCollisions(float delta) final;

    /**
     * Returns the velocity of the object
     * @return The velocity of the object
     */
    [[nodiscard]] const Vector2& velocity() const;

    /**
     * Sets the velocity of the object
     * @param velocity The new velocity of the object
     */
    void setVelocity(Vector2 velocity);

    /**
     * Sets the gravity configuration for the object
     * @param gravity The gravity configuration for the object
     */
    void setGravity(Gravity gravity);
};
