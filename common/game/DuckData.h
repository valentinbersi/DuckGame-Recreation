#pragma once

#include <bitset>

#include "GunData.h"
#include "Object2DData.h"

enum class DuckID {
    // enummerate duck colors
};

typedef u8 DuckFlags;

class DuckData final: public Object2DData {
    constexpr static u8 NFLAGS = 6;

    DuckID _id;
    u8 _life;
    GunData _gun;
    std::bitset<NFLAGS> _flags;

public:
    constexpr static u8 HAS_ARMOR = 0b1;
    constexpr static u8 IS_PLAYING_DEAD = 0b01;
    constexpr static u8 IS_CROUCHING = 0b001;
    constexpr static u8 IS_IN_AIR = 0b0001;
    constexpr static u8 IS_FLAPPING = 0b00001;

    DuckData(u32 objectID, Vector2 position, f32 rotation, DuckID duckID, u8 life, GunData gun,
             DuckFlags flags);

    DuckID duckID() const;

    u8 life() const;

    const GunData& gun() const;

    bool hasArmor() const;

    bool isPlayingDead() const;

    bool isCrouching() const;

    bool isInAir() const;

    bool isFlapping() const;
};
