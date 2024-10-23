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

class GunData {
    GunID id;
};
