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

    DuckState() : playingDead(false), crouching(false), inAir(false), flapping(false),
              beingDamaged(false), moving(false), hasHelmet(false), hasChestplate(false),
              isShooting(false), lookingUp(false), flipped(false), gunEquipped(ItemID::NONE),
              direction(DuckData::Direction::Right) {}

    DuckState(bool playingDead, bool crouching, bool inAir, bool flapping, bool beingDamaged,
          bool moving, bool hasHelmet, bool hasChestplate, bool isShooting, bool lookingUp,
          bool flipped, ItemID gunEquipped, DuckData::Direction direction)

    : playingDead(playingDead), crouching(crouching), inAir(inAir), flapping(flapping),
      beingDamaged(beingDamaged), moving(moving), hasHelmet(hasHelmet),
      hasChestplate(hasChestplate), isShooting(isShooting), lookingUp(lookingUp),
      flipped(flipped), gunEquipped(gunEquipped), direction(direction) {}
};
