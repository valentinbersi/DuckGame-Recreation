#pragma once
#include "EquippableWeapon.h"
#include <unordered_map>
class WeaponFactory{

    static std::unordered_map<GunID, std::function<std::unique_ptr<EquippableWeapon>()>> factory;
    static void inicializeFactory();

public:
    static std::unique_ptr<EquippableWeapon> createItem(GunID id);
};