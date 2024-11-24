#include "DuckData.h"

#include <utility>

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
    return *this;
}

DuckData::DuckData(DuckData&& other) noexcept:
        SizedObjectData(std::move(other)),
        duckID(other.duckID),
        life(other.life),
        direction(other.direction),
        gunID(other.gunID),
        extraData(other.extraData) {}

DuckData& DuckData::operator=(DuckData&& other) noexcept {
    if (this == &other)
        return *this;

    GameObject2DData::operator=(std::move(other));
    duckID = other.duckID;
    life = other.life;
    direction = other.direction;
    gunID = other.gunID;
    extraData = other.extraData;
    return *this;
}

DuckData::~DuckData() = default;

#define DUCK_DIMENSIONS 2, 2.875f

DuckData::DuckData(const Vector2& position, const Id id, const u8 life, const Direction direction,
                   const ItemID gunID, const std::bitset<FlagCount> extraData):
        SizedObjectData(position, DUCK_DIMENSIONS),
        duckID(id),
        life(life),
        direction(direction),
        gunID(gunID),
        extraData(extraData) {}

bool DuckData::operator==(const DuckData& other) const {
    return position.isEqualAprox(other.position) && duckID == other.duckID && life == other.life &&
           gunID == other.gunID && direction == other.direction && extraData == other.extraData;
}
