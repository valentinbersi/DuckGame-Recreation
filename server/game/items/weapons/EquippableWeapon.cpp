#include "EquippableWeapon.h"

EquippableWeapon::EquippableWeapon(ItemID id, u8 ammo, float recoil, float dispersion):
        GameObject(nullptr),
        ammo(ammo),
        id(id),
        firing(false),
        recoil(recoil),
        dispersion(dispersion) {}

ItemID EquippableWeapon::getID() const { return id; }

EquippableWeapon::~EquippableWeapon() = default;
