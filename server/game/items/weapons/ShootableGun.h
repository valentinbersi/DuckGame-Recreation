#pragma once

#include <list>

#include "CollisionObject.h"
#include "EquippableWeapon.h"

class RayCast;

class ShootableGun: public EquippableWeapon {
protected:
    std::list<RayCast*> bullets;
    /**
     * Generates a bullet and adds it as a child of the weapon
     * @param direction The direction of the bullet
     * @param reach The distance the bullet will travel
     * @return The RayCast object representing the bullet
     */
    RayCast* generateBullet(const Vector2& direction, float reach);

public:
    ShootableGun() = delete;
    ShootableGun(const ShootableGun& other) = delete;
    ShootableGun(ShootableGun&& other) noexcept = delete;
    ShootableGun& operator=(const ShootableGun& other) = delete;
    ShootableGun& operator=(ShootableGun&& other) noexcept = delete;
    ~ShootableGun() override;

    /**
     * Creates a new ShootableGun
     * @param id The id of the weapon
     * @param ammo The ammo of the weapon
     * @param recoil The recoil of the weapon
     */
    ShootableGun(ItemID id, u8 ammo, Vector2 recoil);

    /**
     * Handles the collision of the bullet generated
     * by the ShootableGun
     */
    void onBulletCollision(CollisionObject* object);

    /**
     * Gets the actual bullets on frame
     * @return The bullets on frame as segments
     */
    std::list<Segment2D> status() const final override;
};
