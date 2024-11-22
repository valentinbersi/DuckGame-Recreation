#include "WeaponFactory.h"

#include "LongPistol.h"

#define INVALID_ID "Invalid ItemID"

std::unordered_map<ItemID, std::function<std::unique_ptr<EquippableWeapon>()>>
        WeaponFactory::factory = {
                {ItemID::CowboyPistol,
                 []() { return std::make_unique<CowboyPistol>(ItemID::CowboyPistol); }},
                {ItemID::Magnum, []() { return std::make_unique<Magnum>(ItemID::Magnum); }},
};

std::unique_ptr<EquippableWeapon> WeaponFactory::createWeapon(const ItemID id) {
    const auto function = factory.find(id);
    if (function == factory.end())
        throw std::invalid_argument(INVALID_ID);

    return function->second();
}
