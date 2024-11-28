#pragma once

#include "DuckData.h"
#include "ItemID.h"

struct DuckState {
    bool playingDead;
    bool inAir;
    bool flapping;
    bool beingDamaged;
    bool moving;
    bool hasHelmet;
    bool hasChestplate;
    bool isShooting;
    bool lookingUp;
    bool flipped;
    bool hasGun;
    bool noMoreBullets;
    ItemID gunEquipped;
    DuckData::Direction direction;

    DuckState():
            playingDead(false),
            inAir(false),
            flapping(false),
            beingDamaged(false),
            moving(false),
            hasHelmet(false),
            hasChestplate(false),
            isShooting(false),
            lookingUp(false),
            flipped(false),
            hasGun(false),
            noMoreBullets(false),
            gunEquipped(ItemID::NONE),
            direction(DuckData::Direction::Right) {}

    DuckState(bool playingDead, bool inAir, bool flapping, bool beingDamaged, bool moving,
              bool hasHelmet, bool hasChestplate, bool isShooting, bool lookingUp, bool flipped,
              bool hasGun, bool noMoreBullets, ItemID gunEquipped, DuckData::Direction direction)

            :
            playingDead(playingDead),
            inAir(inAir),
            flapping(flapping),
            beingDamaged(beingDamaged),
            moving(moving),
            hasHelmet(hasHelmet),
            hasChestplate(hasChestplate),
            isShooting(isShooting),
            lookingUp(lookingUp),
            flipped(flipped),
            hasGun(hasGun),
            noMoreBullets(noMoreBullets),
            gunEquipped(gunEquipped),
            direction(direction) {}
};
