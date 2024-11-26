#include "EquippableWeapon.h"

#include <utility>

EquippableWeapon::EquippableWeapon(const ItemID id, const u8 ammo, Vector2 recoil,
                                   const float dispersion):
        ammo(ammo), id(id), firing(false), recoil(std::move(recoil)), dispersion(dispersion) {
    registerEvent<const Vector2&>(Events::Fired);
    registerEvent(Events::NoMoreBullets);
}

ItemID EquippableWeapon::getID() const { return id; }

EquippableWeapon::~EquippableWeapon() = default;
