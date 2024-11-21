#include "EquippableWeapon.h"

EquippableWeapon::EquippableWeapon(ItemID id): GameObject(), id(id) {}

ItemID EquippableWeapon::getID() const {return id;}

EquippableWeapon::~EquippableWeapon() = default;
