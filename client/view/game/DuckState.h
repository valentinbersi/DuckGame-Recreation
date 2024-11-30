#pragma once

#include "DuckData.h"
#include "ItemID.h"

struct DuckState {
    bool playingDead;
    bool inAir;
    bool flapping;
    bool moving;
    bool hasHelmet;
    bool hasChestplate;
    bool isShooting;
    bool lookingUp;
    bool flipped;
    bool hasGun;
    bool noMoreBullets;
    bool isDead;
    ItemID gunEquipped;
    DuckData::Direction direction;

    DuckState():
            playingDead(false),
            inAir(false),
            flapping(false),
            moving(false),
            hasHelmet(false),
            hasChestplate(false),
            isShooting(false),
            lookingUp(false),
            flipped(false),
            hasGun(false),
            noMoreBullets(false),
            isDead(false),
            gunEquipped(ItemID::NONE),
            direction(DuckData::Direction::Right) {}

    DuckState(bool playingDead, bool inAir, bool flapping, bool moving, bool hasHelmet,
              bool hasChestplate, bool isShooting, bool lookingUp, bool flipped, bool hasGun,
              bool noMoreBullets, bool isDead, ItemID gunEquipped, DuckData::Direction direction)

            :
            playingDead(playingDead),
            inAir(inAir),
            flapping(flapping),
            moving(moving),
            hasHelmet(hasHelmet),
            hasChestplate(hasChestplate),
            isShooting(isShooting),
            lookingUp(lookingUp),
            flipped(flipped),
            hasGun(hasGun),
            noMoreBullets(noMoreBullets),
            isDead(isDead),
            gunEquipped(gunEquipped),
            direction(direction) {}
};
