#pragma once

#include "CollisionObject.h"
#include "Vector2.h"

class PhysicsObject: public CollisionObject {
public:
    enum class Gravity : u8 { Enabled, Disabled };

private:
    Vector2 _velocity;
    Vector2 lastSafePosition;
    Gravity gravity;

protected:
    PhysicsObject(const PhysicsObject& other);
    PhysicsObject& operator=(const PhysicsObject& other);
    PhysicsObject(PhysicsObject&& other) noexcept;
    PhysicsObject& operator=(PhysicsObject&& other) noexcept;

    /**
     * Creates a new physics object
     * @param parent The parent object
     * @param position The position of the object
     * @param rotation The rotation of the object
     * @param collisionLayer The collision layer of the object
     * @param collisionMask The collision mask of the object
     * @param shape The shape of the object
     * @param initialVelocity The initial velocity of the object
     * @param gravity the gravity configuration for this object
     */
    PhysicsObject(Object* parent, Vector2 position, float rotation, u32 collisionLayer,
                  u32 collisionMask, std::unique_ptr<Shape2D> shape, Vector2 initialVelocity,
                  Gravity gravity);

public:
    PhysicsObject() = delete;
    ~PhysicsObject() override;

    /**
     * Apply gravity to the object
     * @param delta The time since the last update
     */
    void updateInternal(float delta) final;

    /**
     * Calculate the new position of the object based on its velocity. If it collides with
     */
    void processCollisions() final;

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
