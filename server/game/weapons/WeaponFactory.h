#pragma once
#include "Weapon.h"
#include "unordered_map"

class WeaponFactory {
private:
    static std::unordered_map<GunID, std::function<std::unique_ptr<Weapon>()>> factory;
    static std::unique_ptr<Weapon> inicializeFactory();

public:
    static std::unique_ptr<Weapon> createWeapon(GunID id);
};
