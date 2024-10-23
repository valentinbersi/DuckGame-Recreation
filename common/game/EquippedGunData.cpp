#include "EquippedGunData.h"

EquippedGunData::EquippedGunData(const GunID gunID): _id(gunID) {}

GunID EquippedGunData::id() const { return _id; }