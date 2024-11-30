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
    direction = other.direction;
    gunID = other.gunID;
    extraData = other.extraData;
    roundsWon = other.roundsWon;
    return *this;
}

DuckData::DuckData(DuckData&& other) noexcept:
        SizedObjectData(std::move(other)),
        duckID(other.duckID),
        direction(other.direction),
        gunID(other.gunID),
        extraData(other.extraData),
        roundsWon(other.roundsWon) {}

DuckData& DuckData::operator=(DuckData&& other) noexcept {
    if (this == &other)
        return *this;

    GameObject2DData::operator=(std::move(other));
    duckID = other.duckID;
    direction = other.direction;
    gunID = other.gunID;
    extraData = other.extraData;
    roundsWon = other.roundsWon;
    return *this;
}

DuckData::~DuckData() = default;

#define DUCK_DIMENSIONS 2, 2.875f

DuckData::DuckData(const Vector2& position, const Id id, const Direction direction,
                   const ItemID gunID, const std::bitset<FlagCount> extraData, const u32 roundsWon):
        SizedObjectData(position, DUCK_DIMENSIONS),
        duckID(id),
        direction(direction),
        gunID(gunID),
        extraData(extraData),
        roundsWon(roundsWon) {}

bool DuckData::operator==(const DuckData& other) const {
    return position.isEqualAprox(other.position) && duckID == other.duckID &&
           gunID == other.gunID && direction == other.direction && extraData == other.extraData;
}
