#include "EquippedGunData.h"

EquippedGunData::EquippedGunData(const EquippedGunData& other) = default;

EquippedGunData& EquippedGunData::operator=(const EquippedGunData& other) = default;

EquippedGunData::EquippedGunData(EquippedGunData&& other) noexcept = default;

EquippedGunData& EquippedGunData::operator=(EquippedGunData&& other) noexcept = default;

EquippedGunData::EquippedGunData(const GunID gunID): gunID(gunID) {}
