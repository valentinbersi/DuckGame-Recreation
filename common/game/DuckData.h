#pragma once

#include <bitset>

#include "ItemID.h"
#include "SizedObjectData.h"
#include "Types.h"

/**
 * Relevant data for rendering a duck
 */
struct DuckData final: SizedObjectData {
    constexpr static u8 FlagCount = 12;

    enum class Id : u8 { White = 0x0, Orange = 0x1, Yellow = 0x2, Grey = 0x3, None = 0x4 };
    struct Direction {
        enum Value : u8 { Left = 0x0, Center = 0x1, Right = 0x2 };
        Direction() = delete;
        Direction(const Direction& other);
        Direction(Direction&& other) noexcept;
        Direction& operator=(const Direction& other);
        Direction& operator=(Direction&& other) noexcept;
        /**
         * Construct a direction from a value
         * @param value the value to construct the direction from
         */
        // cppcheck-suppress noExplicitConstructor
        Direction(Value value);  // NOLINT (runtime/explicit)
        /**
         * Construct a direction from a value
         * @param value the value to construct the direction from
         */
        // cppcheck-suppress noExplicitConstructor
        Direction(u8 value);  // NOLINT (runtime/explicit)

        /**
         * Convert the direction to a value
         * @return the value of the direction
         */
        // cppcheck-suppress noExplicitConstructor
        operator Value() const;

        /**
            * Push the direction to the right, if the direction was left, it will end up being
            center
            */
        void pushRight();

        /**
            * Push the direction to the left, if the direction was right, it will end up being
            center
            */
        void pushLeft();

    private:
        Value value;
    };

    Id duckID;
    Direction direction;
    ItemID gunID;
    std::bitset<FlagCount> extraData;
    u32 roundsWon;

    DuckData() = delete;
    DuckData(const DuckData& other);
    DuckData& operator=(const DuckData& other);
    DuckData(DuckData&& other) noexcept;
    DuckData& operator=(DuckData&& other) noexcept;
    ~DuckData() override;

    struct Flag {
        Flag() = delete;
        Flag(const Flag& other) = delete;
        Flag(Flag&& other) noexcept = delete;
        Flag& operator=(const Flag& other) = delete;
        Flag& operator=(Flag&& other) noexcept = delete;
        ~Flag() = delete;

        enum Value : u16 {
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
            NoMoreBullets = 0b10000000000,
            IsDead = 0b100000000000
        };

        struct Index {
            Index() = delete;
            Index(const Index& other) = delete;
            Index(Index&& other) noexcept = delete;
            Index& operator=(const Index& other) = delete;
            Index& operator=(Index&& other) noexcept = delete;
            ~Index() = delete;

            enum Value : u8 {
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
                NoMoreBullets = 10,
                IsDead = 11
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
     * @param roundsWon the number of rounds the duck has won
     */
    DuckData(const Vector2& position, Id id, Direction direction, ItemID gunID,
             std::bitset<FlagCount> extraData, u32 roundsWon);

    /**
     * Check if this DuckData is equal to the other DuckData
     * @param other the other DuckData
     * @return true if the DuckData is equal to the other DuckData
     */
    bool operator==(const DuckData& other) const;
};
