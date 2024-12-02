#pragma once

#include "ShootableGun.h"


class CollisionObject;
class LongPistol final: public ShootableGun {
    float reach;
    bool firing;
    bool fireNextFrame;
    RandomFloatGenerator randomGenerator;
    RayCast* bullet;

    /**
     * Handles the collision of the bullet
     * @param object The object that the bullet collided with
     */
    void onBulletCollision(CollisionObject* object);

public:
    LongPistol() = delete;
    LongPistol(const LongPistol& other) = delete;
    LongPistol(LongPistol&& other) noexcept = delete;
    LongPistol& operator=(const LongPistol& other) = delete;
    LongPistol& operator=(LongPistol&& other) noexcept = delete;

    /**
     * Creates a new LongPistol
     * @param id The id of the weapon
     * @param ammo The ammo of the weapon
     * @param recoil The recoil of the weapon
     * @param reach The reach of the weapon
     * @param dispersion The dispersion of the weapon
     */
    LongPistol(ItemID id, u8 ammo, Vector2 recoil, float reach, float dispersion);

    /**
     * Remove the bullet shot in the previous frame
     * @param delta The time since the last frame
     */
    void update(float delta) override;

    /**
     * Actionates the weapon
     */
    void actionate() override;

    /**
     * Deactionates the weapon
     */
    void deactionate() override;

    ~LongPistol() override;
};
