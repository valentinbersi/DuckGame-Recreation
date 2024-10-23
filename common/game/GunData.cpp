#include "GunData.h"

GunData::GunData(GunID id): _id(id) {}

GunID GunData::id() const { return _id; }