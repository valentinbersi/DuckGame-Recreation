#pragma once

#include "EquippableWeapon.h"

class LongPistol final: public EquippableWeapon {
    float reach;
    bool firing;
    RandomFloatGenerator randomGenerator;

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
     * Actionates the weapon
     * @return The recoil of the weapon
     */
    void actionate() override;

    /**
     * Deactionates the weapon
     * @return The recoil of the weapon
     */
    void deactionate() override;

    ~LongPistol() override;
};
