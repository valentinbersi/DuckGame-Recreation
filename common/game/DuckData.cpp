#include "DuckData.h"

#include <utility>

DuckData::Direction::Direction(const Direction& other): value(other.value) {}

DuckData::Direction::Direction(Direction&& other) noexcept: value(other.value) {}

DuckData::Direction& DuckData::Direction::operator=(const Direction& other) {
    if (this == &other)
        return *this;

    value = other.value;
    return *this;
}

DuckData::Direction& DuckData::Direction::operator=(Direction&& other) noexcept {
    if (this == &other)
        return *this;

    value = other.value;
    return *this;
}

DuckData::Direction::Direction(const Value value): value(value) {}

DuckData::Direction::Direction(u8 value): value(static_cast<Value>(value)) {}

DuckData::Direction::operator Value() const { return value; }

void DuckData::Direction::pushRight() {
    if (value == Left)
        value = Center;
    else
        value = Right;
}

void DuckData::Direction::pushLeft() {
    if (value == Right)
        value = Center;
    else
        value = Left;
}

DuckData::DuckData(const DuckData& other) = default;

DuckData& DuckData::operator=(const DuckData& other) {
    if (this == &other)
        return *this;

    GameObject2DData::operator=(other);
    duckID = other.duckID;
    life = other.life;
    direction = other.direction;
    gunID = other.gunID;
    extraData = other.extraData;
    wonRounds = other.wonRounds;
    return *this;
}

DuckData::DuckData(DuckData&& other) noexcept:
        SizedObjectData(std::move(other)),
        duckID(other.duckID),
        life(other.life),
        direction(other.direction),
        gunID(other.gunID),
        extraData(other.extraData),
        wonRounds(other.wonRounds) {}

DuckData& DuckData::operator=(DuckData&& other) noexcept {
    if (this == &other)
        return *this;

    GameObject2DData::operator=(std::move(other));
    duckID = other.duckID;
    life = other.life;
    direction = other.direction;
    gunID = other.gunID;
    extraData = other.extraData;
    wonRounds = other.wonRounds;
    return *this;
}

DuckData::~DuckData() = default;

#define DUCK_DIMENSIONS 2, 2.875f

DuckData::DuckData(const Vector2& position, const Id id, const i8 life, const Direction direction,
                   const ItemID gunID, const std::bitset<FlagCount> extraData, u32 wonRounds):
        SizedObjectData(position, DUCK_DIMENSIONS),
        duckID(id),
        life(life),
        direction(direction),
        gunID(gunID),
        extraData(extraData),
        wonRounds(wonRounds) {}

bool DuckData::operator==(const DuckData& other) const {
    return position.isEqualAprox(other.position) && duckID == other.duckID && life == other.life &&
           gunID == other.gunID && direction == other.direction && extraData == other.extraData;
}
