#include "DuckData.h"

#include <utility>

#include "Math.h"

DuckData::DuckData(const DuckData& other) = default;

DuckData& DuckData::operator=(const DuckData& other) {
    if (this == &other)
        return *this;

    GameObject2DData::operator=(other);
    duckID = other.duckID;
    life = other.life;
    gunID = other.gunID;
    extraData = other.extraData;
    return *this;
}

DuckData::DuckData(DuckData&& other) noexcept:
        SizedObjectData(std::move(other)),
        duckID(other.duckID),
        life(other.life),
        gunID(other.gunID),
        extraData(other.extraData) {}

DuckData& DuckData::operator=(DuckData&& other) noexcept {
    if (this == &other)
        return *this;

    GameObject2DData::operator=(std::move(other));
    duckID = other.duckID;
    life = other.life;
    gunID = other.gunID;
    extraData = other.extraData;
    return *this;
}

DuckData::~DuckData() = default;

DuckData::DuckData(Vector2 position, const DuckID duckID, const u8 life, const ItemID gunID,
                   const DuckFlag extraData):
        SizedObjectData(position, 2, 2.875f),
        duckID(duckID),
        life(life),
        gunID(gunID),
        extraData(extraData) {}

bool DuckData::operator==(const DuckData& other) const {
    return position == other.position && duckID == other.duckID && life == other.life &&
           extraData == other.extraData;
}
