#pragma once

#include <memory>

#include "EquippableWeapon.h"
#include "unordered_map"

class WeaponFactory {
    /**
     * HashMap used to create Weapon
     */
    static std::unordered_map<ItemID, std::function<std::unique_ptr<EquippableWeapon>()>> factory;

public:
    /**
     * Creates Weapon base on given ItemID, throws exception
     * in case id does not corresponde to any Wapon
     * @param id
     * @return unique pointer to Created Weapon
     * @throws std::invalid_argument
     */
    static std::unique_ptr<EquippableWeapon> createWeapon(const ItemID id);
};
