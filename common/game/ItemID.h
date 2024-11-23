#pragma once

#include <functional>

#include "RandomGenerator.h"
#include "Types.h"

class ItemID {
public:
    enum Value : unsigned char {
        Grenade = 0x0,
        Banana = 0x1,
        PewPewLaser = 0x2,
        LaserRifle = 0x3,
        Ak47 = 0x4,
        DuelPistol = 0x5,
        CowboyPistol = 0x6,
        Magnum = 0x7,
        Shotgun = 0x8,
        Sniper = 0x9,
        Helmet = 0xA,
        Armor = 0x0B,
        NONE = 0x0C
    };

    ItemID() = delete;

    // cppcheck-suppress noExplicitConstructor
    ItemID(Value value);  // NOLINT(runtime/explicit)

    // cppcheck-suppress noExplicitConstructor
    ItemID(unsigned char value);  // NOLINT(runtime/explicit)

    [[nodiscard]] operator Value() const;

    static RandomIntGenerator randomGenerator;

    /**
     * Generates random ItemID
     * @return random ItemID
     */
    static ItemID randomItemID();

private:
    Value _value;

    friend struct std::hash<ItemID>;

    friend struct std::equal_to<ItemID>;
};

template <>
struct std::hash<ItemID> {
    std::size_t operator()(const ItemID& itemID) const {
        return std::hash<ItemID::Value>()(itemID._value);
    }
};

template <>
struct std::equal_to<ItemID> {
    bool operator()(const ItemID& firstID, const ItemID& secondID) const {
        return firstID._value == secondID._value;
    }
};
