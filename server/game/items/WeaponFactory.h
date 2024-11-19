#pragma once
#include <unordered_map>

#include "EquippableWeapon.h"
class WeaponFactory {

    static std::unordered_map<GunID, std::function<std::unique_ptr<EquippableWeapon>()>> factory;
    static void inicializeFactory();

public:
    static std::unique_ptr<EquippableWeapon> createItem(GunID id);
};