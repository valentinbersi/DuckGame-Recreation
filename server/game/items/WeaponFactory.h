#pragma once
#include <memory>
#include <unordered_map>

#include "EquippableWeapon.h"
class WeaponFactory {

    static std::unordered_map<ItemID, std::function<std::unique_ptr<EquippableWeapon>()>> factory;
    static void inicializeFactory();

public:
    static std::unique_ptr<EquippableWeapon> createItem(ItemID id);
};
