#pragma once

#include <bitset>
#include <cstdint>
#include <memory>

#include "EquippedGunData.h"
#include "GameObject2DData.h"

using u8 = std::uint8_t;

enum class DuckID : u8 { White = 0x0, Orange = 0x1, Yellow = 0x2, Grey = 0x3 };

/**
 * Relevant data for rendering a duck
 */
struct DuckData final: GameObject2DData {
    constexpr static u8 NFLAGS = 10;

    DuckID duckID;
    u8 life;
    std::unique_ptr<EquippedGunData> gun;
    std::bitset<NFLAGS> extraData;

    DuckData() = delete;
    DuckData(const DuckData& other) = delete;
    DuckData& operator=(const DuckData& other) = delete;
    DuckData(DuckData&& other) noexcept;
    DuckData& operator=(DuckData&& other) noexcept;
    ~DuckData() override;

    using DuckFlag = u16;

    constexpr static DuckFlag ARMOR = 0b1;
    constexpr static DuckFlag HELMET = 0b10;
    constexpr static DuckFlag PLAYING_DEAD = 0b100;
    constexpr static DuckFlag CROUCHING = 0b1000;
    constexpr static DuckFlag IN_AIR = 0b10000;
    constexpr static DuckFlag FLAPPING = 0b100000;
    constexpr static DuckFlag BEING_DAMAGED = 0b1000000;
    constexpr static DuckFlag MOVING_RIGHT = 0b10000000;
    constexpr static DuckFlag MOVING_LEFT = 0b100000000;
    constexpr static DuckFlag LOOKING_UP = 0b1000000000;

    constexpr static u8 ARMOR_INDEX = 0;
    constexpr static u8 HELMET_INDEX = 1;
    constexpr static u8 PLAYING_DEAD_INDEX = 2;
    constexpr static u8 CROUCHING_INDEX = 3;
    constexpr static u8 IN_AIR_INDEX = 4;
    constexpr static u8 FLAPPING_INDEX = 5;
    constexpr static u8 BEING_DAMAGED_INDEX = 6;
    constexpr static u8 MOVING_RIGHT_INDEX = 7;
    constexpr static u8 MOVING_LEFT_INDEX = 8;
    constexpr static u8 LOOKING_UP_INDEX = 9;

    /**
     * Construct a DuckData object
     * @param position the object's position
     * @param rotation the object's rotation
     * @param duckID the duck's ID
     * @param life the life of the duck
     * @param gun the gun of the duck
     * @param extraData actions the duck is performing and armor data
     */
    DuckData(Vector2 position, float rotation, DuckID duckID, u8 life,
             std::unique_ptr<EquippedGunData> gun, DuckFlag extraData);
};
