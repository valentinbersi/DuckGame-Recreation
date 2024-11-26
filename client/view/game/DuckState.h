#pragma once

#include "ItemID.h"
#include "DuckData.h"

struct DuckState {
    bool playingDead;
    bool crouching;
    bool inAir;
    bool flapping;
    bool beingDamaged;
    bool moving;
    bool hasHelmet;
    bool hasChestplate;
    bool isShooting;
    bool lookingUp;
    bool flipped;
    ItemID gunEquipped;
    DuckData::Direction direction;
};
