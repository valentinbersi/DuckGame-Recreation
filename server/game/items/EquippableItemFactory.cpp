#include "EquippableItemFactory.h"

#include "Ak47.h"
#include "Config.h"
#include "EquippableArmor.h"
#include "LongPistol.h"
#include "Math.h"
#include "ShotGun.h"
#include "Sniper.h"
#include "EquippableGrenade.h"


#define INVALID_ID "Invalid ItemID"

std::unordered_map<ItemID, std::function<std::unique_ptr<EquippableItem>(u8)>>
        EquippableItemFactory::factory = {

                {ItemID::DuelPistol,
                 [](u8 ammo) {
                     return std::make_unique<LongPistol>(
                             ItemID::DuelPistol, ammo, Config::Weapons::DuelPistol::recoil(),
                             Config::Weapons::DuelPistol::reach(),
                             Math::toRadians(Config::Weapons::DuelPistol::dispersion()));
                 }},
                {ItemID::CowboyPistol,
                 [](u8 ammo) {
                     return std::make_unique<LongPistol>(
                             ItemID::CowboyPistol, ammo, Config::Weapons::CowboyPistol::recoil(),
                             Config::Weapons::CowboyPistol::reach(),
                             Math::toRadians(Config::Weapons::CowboyPistol::dispersion()));
                 }},
                {ItemID::Magnum,
                 [](u8 ammo) {
                     return std::make_unique<LongPistol>(
                             ItemID::Magnum, ammo, Config::Weapons::Magnum::recoil(),
                             Config::Weapons::Magnum::reach(),
                             Math::toRadians(Config::Weapons::Magnum::dispersion()));
                 }},
                {ItemID::Shotgun,
                 [](u8 ammo) {
                     return std::make_unique<Shotgun>(
                             ItemID::Shotgun, ammo, Config::Weapons::Shotgun::recoil(),
                             Config::Weapons::Shotgun::minReach(),
                             Config::Weapons::Shotgun::maxReach(),
                             Math::toRadians(Config::Weapons::Shotgun::dispersion()),
                             Config::Weapons::Shotgun::pelletsPerShot());
                 }},
                {ItemID::Sniper,
                 [](u8 ammo) {
                     return std::make_unique<Sniper>(ItemID::Sniper, ammo,
                                                     Config::Weapons::Sniper::recoil(),
                                                     Config::Weapons::Sniper::reach(),
                                                     Config::Weapons::Sniper::dispersion(),
                                                     Config::Weapons::Sniper::reloadTime());
                 }},
                {ItemID::Ak47,
                 [](u8 ammo) {
                     return std::make_unique<Ak47>(
                             ItemID::Ak47, ammo, Config::Weapons::Ak47::recoil(),
                             Config::Weapons::Ak47::reach(),
                             Math::toRadians(Config::Weapons::Ak47::minDispersion()),
                             Math::toRadians(Config::Weapons::Ak47::midDispersion()),
                             Math::toRadians(Config::Weapons::Ak47::maxDispersion()),
                             Config::Weapons::Ak47::timeBetweenShots());
                 }},
                {ItemID::Helmet,
                 []([[maybe_unused]] u8 ammo) {
                     return std::make_unique<EquippableArmor>(ItemID::Helmet,
                                                              Config::Armor::helmet());
                 }},
                {ItemID::Armor, []([[maybe_unused]] u8 ammo) {
                     return std::make_unique<EquippableArmor>(ItemID::Armor,
                                                              Config::Armor::armor());
                 }},
                 {ItemID::Grenade,
                 [](u8 ammo) {
                     return std::make_unique<EquippableGrenade>(
                             ItemID::Grenade, ammo, Config::Weapons::Grenade::explosionTime());
                 }},
                };

std::unique_ptr<EquippableItem> EquippableItemFactory::createEquippableItem(const ItemID id,
                                                                            u8 ammo) {
    const auto function = factory.find(id);
    if (function == factory.end())
        throw std::invalid_argument(INVALID_ID);

    return function->second(ammo);
}
