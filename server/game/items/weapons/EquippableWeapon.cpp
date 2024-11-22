#include "EquippableWeapon.h"

EquippableWeapon::EquippableWeapon() = default;

EquippableWeapon::EquippableWeapon(ItemID id, u8 ammo, float recoil, float dispersion): 
    GameObject(), id(id), ammo(ammo), firing(false) , recoil(recoil), dispersion(dispersion) {}

ItemID EquippableWeapon::getID() const {return id;}

EquippableWeapon::~EquippableWeapon() = default;
