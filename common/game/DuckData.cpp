#include "DuckData.h"

#include <utility>
#include "Math.h"

DuckData::DuckData(DuckData&& other) noexcept:
        GameObject2DData(std::move(other)),
        duckID(other.duckID),
        life(other.life),
        gun(std::move(other.gun)),
        extraData(other.extraData) {}

DuckData& DuckData::operator=(DuckData&& other) noexcept {
    if (this == &other)
        return *this;

    GameObject2DData::operator=(std::move(other));
    duckID = other.duckID;
    life = other.life;
    gun = std::move(other.gun);
    extraData = other.extraData;
    return *this;
}

DuckData::~DuckData() = default;

DuckData::DuckData(Vector2 position, const float rotation, const DuckID duckID, const u8 life,
                   std::unique_ptr<EquippedGunData> gun, const DuckFlag extraData):
        GameObject2DData(GameObject2DID::Duck, std::move(position), rotation),
        duckID(duckID),
        life(life),
        gun(std::move(gun)),
        extraData(extraData) {}

bool DuckData::operator==(const DuckData& other) const {
    return objectID == other.objectID &&
           object2DID == other.object2DID &&
           position == other.position &&
           Math::isEqualAprox(rotation, other.rotation) &&
           duckID == other.duckID &&
           life == other.life &&
           gun->gunID == other.gun->gunID &&
           extraData == other.extraData;
}
