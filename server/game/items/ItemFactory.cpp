#include "ItemFactory.h"

#include "Config.h"
#define INVALID_ID "Invalid ItemID"

#define GRENADE_DIMENSIONS 1.25, 1.375
#define BANANA_DIMENSIONS 1.75, 0.875
#define PEW_PEW_LASER_DIMENSIONS 3.25, 1.25
#define LASER_RIFLE_DIMENSIONS 2.875, 1.5
#define AK47_DIMENSIONS 4, 1.375
#define DUEL_PISTOL_DIMENSIONS 1.5, 1.125
#define COWBOY_PISTOL_DIMENSIONS 2.75, 1.375
#define MAGNUM_DIMENSIONS 2.5, 1.375
#define SHOTGUN_DIMENSIONS 3.375, 1.125
#define SNIPER_DIMENSIONS 4.125, 1.125
#define HELMET_DIMENSIONS 1.625, 1.875
#define ARMOR_DIMENSIONS 1.5, 1.375

std::unordered_map<ItemID, std::function<std::unique_ptr<Item>(u8)>> ItemFactory::factory = {
        {ItemID::Grenade,
         [](u8 ammo) { return std::make_unique<Item>(GRENADE_DIMENSIONS, ItemID::Grenade, ammo); }},
        {ItemID::Banana,
         [](u8 ammo) { return std::make_unique<Item>(BANANA_DIMENSIONS, ItemID::Banana, ammo); }},
        {ItemID::PewPewLaser,
         [](u8 ammo) {
             return std::make_unique<Item>(PEW_PEW_LASER_DIMENSIONS, ItemID::PewPewLaser, ammo);
         }},
        {ItemID::LaserRifle,
         [](u8 ammo) {
             return std::make_unique<Item>(LASER_RIFLE_DIMENSIONS, ItemID::LaserRifle, ammo);
         }},
        {ItemID::Ak47,
         [](u8 ammo) { return std::make_unique<Item>(AK47_DIMENSIONS, ItemID::Ak47, ammo); }},
        {ItemID::DuelPistol,
         [](u8 ammo) {
             return std::make_unique<Item>(DUEL_PISTOL_DIMENSIONS, ItemID::DuelPistol, ammo);
         }},
        {ItemID::CowboyPistol,
         [](u8 ammo) {
             return std::make_unique<Item>(COWBOY_PISTOL_DIMENSIONS, ItemID::CowboyPistol, ammo);
         }},
        {ItemID::Magnum,
         [](u8 ammo) { return std::make_unique<Item>(MAGNUM_DIMENSIONS, ItemID::Magnum, ammo); }},
        {ItemID::Shotgun,
         [](u8 ammo) { return std::make_unique<Item>(SHOTGUN_DIMENSIONS, ItemID::Shotgun, ammo); }},
        {ItemID::Sniper,
         [](u8 ammo) { return std::make_unique<Item>(SNIPER_DIMENSIONS, ItemID::Sniper, ammo); }},
        {ItemID::Helmet,
         [](u8 ammo) { return std::make_unique<Item>(HELMET_DIMENSIONS, ItemID::Helmet, ammo); }},
        {ItemID::Armor,
         [](u8 ammo) { return std::make_unique<Item>(ARMOR_DIMENSIONS, ItemID::Armor, ammo); }}};


std::unique_ptr<Item> ItemFactory::createItem(const ItemID id, u8 ammo, Force force) {
    const auto function = factory.find(id);
    if (function == factory.end())
        throw std::invalid_argument(INVALID_ID);

    if (force == Force::Yes) {
        ammo = Config::getDefaultAmmo(id);
    }
    return function->second(ammo);
}
