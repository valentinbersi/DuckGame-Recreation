#pragma once

#include "CollisionObject.h"
#include "Vector2.h"

class PhysicsObject: public CollisionObject {
public:
    enum class Gravity : u8 { Enabled, Disabled };

private:
    Gravity gravity;

protected:
    Vector2 _velocity;
    bool _onGround;

    /**
     * Creates a new physics object
     * @param parent The parent object
     * @param position The position of the object
     * @param layers The layer the object is in
     * @param scannedLayers The layer the object scans for collisions
     * @param width The width of the object
     * @param height The height of the object
     * @param gravity the gravity configuration for this object
     */
    PhysicsObject(GameObject* parent, const Vector2& position, std::bitset<LayersCount> layers,
                  std::bitset<LayersCount> scannedLayers, float width, float height,
                  Gravity gravity);

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
     * Sets the gravity configuration for the object
     * @param gravity The gravity configuration for the object
     */
    void setGravity(Gravity gravity);
};
