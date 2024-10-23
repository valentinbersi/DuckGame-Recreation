#pragma once

#include "Types.h"

enum class GunID : u8 {
    Granade,
    Banana,
    PewPewLaser,
    LaserRifle,
    Ak47,
    DuelPistol,
    CowboyPistol,
    Magnum,
    Shotgun,
    Sniper
};

/**
 * Relevant data for rendering a gun in the game
 */
class EquippedGunData {
    GunID _id;

public:
    /**
     * Construct a GunData with the given GunID
     */
    explicit EquippedGunData(GunID gunID);

    /**
     * Get the GunID of the gun
     * @return the GunID of the gun
     */
    [[nodiscard]] GunID id() const;

    /**
     * Get the data of the gun
     */
    [[nodiscard]] std::string data() const;
};
