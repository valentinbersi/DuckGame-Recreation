#pragma once

#include "EquippableWeapon.h"

class Shotgun final: public EquippableWeapon {
    float minReach;
    float maxReach;
    bool firing;
    u8 pellets;
    bool hasToReload;
    RandomFloatGenerator randomDistanceGenerator;
    RandomFloatGenerator randomDispersionGenerator;

    /**
     * Generates all necesaries bullets
     */
    void generateBullet();

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
     * @param reach The reach of the weapon
     * @param dispersion The dispersion of the weapon
     */
    Shotgun(ItemID id, u8 ammo, Vector2 recoil, float minReach, float maxReach, float dispersion,
            u8 pellets);

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
