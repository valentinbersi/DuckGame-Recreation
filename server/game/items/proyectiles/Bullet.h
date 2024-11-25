#pragma once

#include "PhysicsObject.h"
#include "Types.h"

class ItemID;

class Bullet final: public PhysicsObject {
    constexpr static u8 INeedMoreBullets = 0;

    u8 damage;
    u8 tiles;

    /**
     *  Called when the bullet collides with an object
     *  @param object The object the bullet collided with
     */
    void onCollision(CollisionObject* object) const;

public:
    Bullet() = delete;
    Bullet(const Bullet& other) = delete;
    Bullet(Bullet&& other) noexcept = delete;
    Bullet& operator=(const Bullet& other) = delete;
    Bullet& operator=(Bullet&& other) noexcept = delete;

    /**
     * Creates a new Bullet
     * @param damage The damage of the bullet
     * @param velocity The velocity of the bullet
     * @param tiles The tiles the bullet can travel
     */
    Bullet(u8 damage, Vector2 velocity, u8 tiles);

    ~Bullet() override;
};
