#include "EquippedGunData.h"

EquippedGunData::EquippedGunData(const GunID gunID): _id(gunID) {}

GunID EquippedGunData::id() const { return _id; }

std::string EquippedGunData::data() const { return std::to_string(static_cast<u8>(_id)); }