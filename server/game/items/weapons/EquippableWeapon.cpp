#include "EquippableWeapon.h"

EquippableWeapon::EquippableWeapon(const ItemID id, const u8 ammo, Vector2 recoil,
                                   const float dispersion):
        GameObject(nullptr),
        ammo(ammo),
        id(id),
        firing(false),
        recoil(std::move(recoil)),
        dispersion(dispersion) {}

ItemID EquippableWeapon::getID() const { return id; }

EquippableWeapon::~EquippableWeapon() = default;
