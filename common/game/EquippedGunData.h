#pragma once

#include "Types.h"

enum class GunID : u8 {
    Granade = 0x0,
    Banana = 0x1,
    PewPewLaser = 0x2,
    LaserRifle = 0x3,
    Ak47 = 0x4,
    DuelPistol = 0x5,
    CowboyPistol = 0x6,
    Magnum = 0x7,
    Shotgun = 0x8,
    Sniper = 0x9
};

/**
 * Relevant data for rendering a gun in the game
 */
struct EquippedGunData {
    GunID gunID;

    EquippedGunData() = delete;
    EquippedGunData(const EquippedGunData& other);
    EquippedGunData& operator=(const EquippedGunData& other);
    EquippedGunData(EquippedGunData&& other) noexcept;
    EquippedGunData& operator=(EquippedGunData&& other) noexcept;

    /**
     * Construct a GunData with the given GunID
     */
    explicit EquippedGunData(GunID gunID);
};
