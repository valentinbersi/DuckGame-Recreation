#pragma once

#include "EquippableWeapon.h"

class RayCast;

class ShootableGun: public EquippableWeapon {
protected:
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
};
