#include "EquippableItemFactory.h"

#include "Ak47.h"
#include "Config.h"
#include "EquippableArmor.h"
#include "LongPistol.h"
#include "Math.h"
#include "ShotGun.h"
#include "Sniper.h"


#define INVALID_ID "Invalid ItemID"

std::unordered_map<ItemID, std::function<std::unique_ptr<EquippableItem>()>>
        EquippableItemFactory::factory = {
                {ItemID::DuelPistol,
                 [] {
                     return std::make_unique<LongPistol>(
                             ItemID::DuelPistol, Config::Weapons::DuelPistol::ammo(),
                             Config::Weapons::DuelPistol::recoil(),
                             Config::Weapons::DuelPistol::reach(),
                             Math::toRadians(Config::Weapons::DuelPistol::dispersion()));
                 }},
                {ItemID::CowboyPistol,
                 [] {
                     return std::make_unique<LongPistol>(
                             ItemID::CowboyPistol, Config::Weapons::CowboyPistol::ammo(),
                             Config::Weapons::CowboyPistol::recoil(),
                             Config::Weapons::CowboyPistol::reach(),
                             Math::toRadians(Config::Weapons::CowboyPistol::dispersion()));
                 }},
                {ItemID::Magnum,
                 [] {
                     return std::make_unique<LongPistol>(
                             ItemID::Magnum, Config::Weapons::Magnum::ammo(),
                             Config::Weapons::Magnum::recoil(), Config::Weapons::Magnum::reach(),
                             Math::toRadians(Config::Weapons::Magnum::dispersion()));
                 }},
                {ItemID::Shotgun,
                 [] {
                     return std::make_unique<Shotgun>(
                             ItemID::Shotgun, Config::Weapons::Shotgun::ammo(),
                             Config::Weapons::Shotgun::recoil(),
                             Config::Weapons::Shotgun::minReach(),
                             Config::Weapons::Shotgun::maxReach(),
                             Math::toRadians(Config::Weapons::Shotgun::dispersion()),
                             Config::Weapons::Shotgun::pelletsPerShot());
                 }},
                {ItemID::Sniper,
                 [] {
                     return std::make_unique<Sniper>(
                             ItemID::Sniper, Config::Weapons::Sniper::ammo(),
                             Config::Weapons::Sniper::recoil(), Config::Weapons::Sniper::reach(),
                             Config::Weapons::Sniper::dispersion(),
                             Config::Weapons::Sniper::reloadTime());
                 }},
                {ItemID::Ak47,
                 [] {
                     return std::make_unique<Ak47>(
                             ItemID::Ak47, Config::Weapons::Ak47::ammo(),
                             Config::Weapons::Ak47::recoil(), Config::Weapons::Ak47::reach(),
                             Math::toRadians(Config::Weapons::Ak47::minDispersion()),
                             Math::toRadians(Config::Weapons::Ak47::midDispersion()),
                             Math::toRadians(Config::Weapons::Ak47::maxDispersion()),
                             Config::Weapons::Ak47::timeBetweenShots());
                 }},
                {ItemID::Helmet,
                 [] {
                     return std::make_unique<EquippableArmor>(ItemID::Helmet,
                                                              Config::Armor::helmet());
                 }},
                {ItemID::Armor, [] {
                     return std::make_unique<EquippableArmor>(ItemID::Armor,
                                                              Config::Armor::armor());
                 }}};

std::unique_ptr<EquippableItem> EquippableItemFactory::createEquippableItem(const ItemID id) {
    const auto function = factory.find(id);
    if (function == factory.end())
        throw std::invalid_argument(INVALID_ID);

    return function->second();
}
