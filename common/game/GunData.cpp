#include "GunData.h"

GunData::GunData(const GunID id): _id(id) {}

GunID GunData::id() const { return _id; }