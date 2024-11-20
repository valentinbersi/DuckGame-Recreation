#pragma once

#include "ItemID.h"

struct DuckState {
    bool playingDead;
    bool crouching;
    bool inAir;
    bool flapping;
    bool beingDamaged;
    bool movingRight;
    bool movingLeft;
    bool hasHelmet;
    bool hasChestplate;
    bool isShooting;
    ItemID gunEquipped;
};
