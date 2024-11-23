#include "ItemFactory.h"

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

std::unordered_map<ItemID, std::function<std::unique_ptr<Item>()>> ItemFactory::factory = {
        {ItemID::Grenade,
         [] { return std::make_unique<Item>(GRENADE_DIMENSIONS, ItemID::Grenade); }},
        {ItemID::Banana, [] { return std::make_unique<Item>(BANANA_DIMENSIONS, ItemID::Banana); }},
        {ItemID::PewPewLaser,
         [] { return std::make_unique<Item>(PEW_PEW_LASER_DIMENSIONS, ItemID::PewPewLaser); }},
        {ItemID::LaserRifle,
         [] { return std::make_unique<Item>(LASER_RIFLE_DIMENSIONS, ItemID::LaserRifle); }},
        {ItemID::Ak47, [] { return std::make_unique<Item>(AK47_DIMENSIONS, ItemID::Ak47); }},
        {ItemID::DuelPistol,
         [] { return std::make_unique<Item>(DUEL_PISTOL_DIMENSIONS, ItemID::DuelPistol); }},
        {ItemID::CowboyPistol,
         [] { return std::make_unique<Item>(COWBOY_PISTOL_DIMENSIONS, ItemID::CowboyPistol); }},
        {ItemID::Magnum, [] { return std::make_unique<Item>(MAGNUM_DIMENSIONS, ItemID::Magnum); }},
        {ItemID::Shotgun,
         [] { return std::make_unique<Item>(SHOTGUN_DIMENSIONS, ItemID::Shotgun); }},
        {ItemID::Sniper, [] { return std::make_unique<Item>(SNIPER_DIMENSIONS, ItemID::Sniper); }},
        {ItemID::Helmet, [] { return std::make_unique<Item>(HELMET_DIMENSIONS, ItemID::Helmet); }},
        {ItemID::Armor, [] { return std::make_unique<Item>(ARMOR_DIMENSIONS, ItemID::Armor); }}};

std::unique_ptr<Item> ItemFactory::createItem(const ItemID id) {
    const auto function = factory.find(id);
    if (function == factory.end())
        throw std::invalid_argument(INVALID_ID);

    return function->second();
}
