#pragma once

#include "EquippableWeapon.h"
#include "RayCast.h"
#include "ShootableGun.h"

class Shotgun final: public ShootableGun {
    float minReach;
    float maxReach;
    bool firing;
    bool fireNextFrame;
    bool hasToReload;
    RandomFloatGenerator randomDistanceGenerator;
    RandomFloatGenerator randomDispersionGenerator;

public:
    Shotgun() = delete;
    Shotgun(const Shotgun& other) = delete;
    Shotgun(Shotgun&& other) noexcept = delete;
    Shotgun& operator=(const Shotgun& other) = delete;
    Shotgun& operator=(Shotgun&& other) noexcept = delete;

    /**
     * Creates a new ShotGun
     * @param id The id of the weapon
     * @param ammo The ammo of the weapon
     * @param recoil The recoil of the weapon
     * @param minReach The minimum reach of the weapon
     * @param maxReach The maximum reach of the weapon
     * @param dispersion The dispersion of the weapon
     * @param pellets The number of pellets of the weapon
     */
    Shotgun(ItemID id, u8 ammo, Vector2 recoil, float minReach, float maxReach, float dispersion,
            u8 pellets);

    /**
     * Update the gun and made it fire if it was actionated
     * @param delta The time since the last frame
     */
    void update(float delta) override;

    /**
     * Actionates the shotgun
     */
    void actionate() override;

    /**
     * Deactionates the shotgun
     */
    void deactionate() override;

    ~Shotgun() override;
};
