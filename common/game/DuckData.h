#pragma once

#include <bitset>

#include "ItemID.h"
#include "SizedObjectData.h"
#include "Types.h"

/**
 * Relevant data for rendering a duck
 */
struct DuckData final: SizedObjectData {
    constexpr static u8 FlagCount = 11;

    enum class Id : u8 { White = 0x0, Orange = 0x1, Yellow = 0x2, Grey = 0x3, None = 0x4 };
    enum class Direction : u8 { Left = 0x0, Right = 0x1 };

    Id duckID;
    i8 life;
    Direction direction;
    ItemID gunID;
    std::bitset<FlagCount> extraData;

    DuckData() = delete;
    DuckData(const DuckData& other);
    DuckData& operator=(const DuckData& other);
    DuckData(DuckData&& other) noexcept;
    DuckData& operator=(DuckData&& other) noexcept;
    ~DuckData() override;

    struct Flag {
        enum Value {
            Armor = 0b1,
            Helmet = 0b10,
            PlayingDead = 0b100,
            Crouching = 0b1000,
            InAir = 0b10000,
            Flapping = 0b100000,
            BeingDamaged = 0b1000000,
            IsMoving = 0b10000000,
            LookingUp = 0b100000000,
            IsShooting = 0b1000000000,
            NoMoreBullets = 0b10000000000
        };

        struct Index {
            enum Value {
                Armor = 0,
                Helmet = 1,
                PlayingDead = 2,
                Crouching = 3,
                InAir = 4,
                Flapping = 5,
                BeingDamaged = 6,
                IsMoving = 7,
                LookingUp = 8,
                IsShooting = 9,
                NoMoreBullets = 10
            };
        };
    };

    /**
     * Construct a DuckData object
     * @param position the object's position
     * @param id the duck's ID
     * @param life the life of the duck
     * @param direction the direction the duck is facing
     * @param gunID the gun the duck is holding
     * @param extraData actions the duck is performing and armor data
     */
    DuckData(const Vector2& position, Id id, i8 life, Direction direction, ItemID gunID,
             std::bitset<FlagCount> extraData);

    /**
     * Check if this DuckData is equal to the other DuckData
     * @param other the other DuckData
     * @return true if the DuckData is equal to the other DuckData
     */
    bool operator==(const DuckData& other) const;
};
