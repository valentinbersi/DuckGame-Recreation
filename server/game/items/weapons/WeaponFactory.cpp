#include "WeaponFactory.h"

#include "Config.h"
#include "LongPistol.h"

#define INVALID_ID "Invalid ItemID"

std::unordered_map<ItemID, std::function<std::unique_ptr<EquippableWeapon>()>>
        WeaponFactory::factory = {
                {ItemID::DuelPistol,
                 [] {
                     return std::make_unique<LongPistol>(ItemID::DuelPistol,
                                                         Config::Weapons::DuelPistol::ammo(),
                                                         Config::Weapons::DuelPistol::recoil(),
                                                         Config::Weapons::DuelPistol::reach(),
                                                         Config::Weapons::DuelPistol::dispersion());
                 }},
                {ItemID::CowboyPistol,
                 [] {
                     return std::make_unique<LongPistol>(
                             ItemID::CowboyPistol, Config::Weapons::CowboyPistol::ammo(),
                             Config::Weapons::CowboyPistol::recoil(),
                             Config::Weapons::CowboyPistol::reach(),
                             Config::Weapons::CowboyPistol::dispersion());
                 }},
                {ItemID::Magnum, [] {
                     return std::make_unique<LongPistol>(
                             ItemID::Magnum, Config::Weapons::Magnum::ammo(),
                             Config::Weapons::Magnum::recoil(), Config::Weapons::Magnum::reach(),
                             Config::Weapons::Magnum::dispersion());
                 }}};

std::unique_ptr<EquippableWeapon> WeaponFactory::createWeapon(const ItemID id) {
    const auto function = factory.find(id);
    if (function == factory.end())
        throw std::invalid_argument(INVALID_ID);

    return function->second();
}
