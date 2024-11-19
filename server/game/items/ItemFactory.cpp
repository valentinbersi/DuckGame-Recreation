#include "ItemFactory.h"
// #define INVALID_ID "Invalid GunID"

// void ItemFactory::inicializeFactory() {
//     factory.insert({GunID::Granade, []() {
//                         return std::make_unique<EquippableItem>(
//                                 GunID::Granade, nullptr, Vector2(), 0,
//                                 std::make_unique<Rectangle>(Vector2(), 0, 0), Vector2());
//                     }});
//     factory.insert({GunID::Banana, []() {
//                         return std::make_unique<EquippableItem>(
//                                 GunID::Banana, nullptr, Vector2(), 0,
//                                 std::make_unique<Rectangle>(Vector2(), 0, 0), Vector2());
//                     }});
//     factory.insert({GunID::PewPewLaser, []() {
//                         return std::make_unique<EquippableItem>(
//                                 GunID::PewPewLaser, nullptr, Vector2(), 0,
//                                 std::make_unique<Rectangle>(Vector2(), 0, 0), Vector2());
//                     }});
//     factory.insert({GunID::LaserRifle, []() {
//                         return std::make_unique<EquippableItem>(
//                                 GunID::LaserRifle, nullptr, Vector2(), 0,
//                                 std::make_unique<Rectangle>(Vector2(), 0, 0), Vector2());
//                     }});
//     factory.insert({GunID::Ak47, []() {
//                         return std::make_unique<EquippableItem>(
//                                 GunID::Ak47, nullptr, Vector2(), 0,
//                                 std::make_unique<Rectangle>(Vector2(), 0, 0), Vector2());
//                     }});
//     factory.insert({GunID::DuelPistol, []() {
//                         return std::make_unique<EquippableItem>(
//                                 GunID::DuelPistol, nullptr, Vector2(), 0,
//                                 std::make_unique<Rectangle>(Vector2(), 0, 0), Vector2());
//                     }});
//     factory.insert({GunID::CowboyPistol, []() {
//                         return std::make_unique<EquippableItem>(
//                                 GunID::CowboyPistol, nullptr, Vector2(), 0,
//                                 std::make_unique<Rectangle>(Vector2(), 0, 0), Vector2());
//                     }});
//     factory.insert({GunID::Magnum, []() {
//                         return std::make_unique<EquippableItem>(
//                                 GunID::Magnum, nullptr, Vector2(), 0,
//                                 std::make_unique<Rectangle>(Vector2(), 0, 0), Vector2());
//                     }});
//     factory.insert({GunID::Shotgun, []() {
//                         return std::make_unique<EquippableItem>(
//                                 GunID::Shotgun, nullptr, Vector2(), 0,
//                                 std::make_unique<Rectangle>(Vector2(), 0, 0), Vector2());
//                     }});
//     factory.insert({GunID::Sniper, []() {
//                         return std::make_unique<EquippableItem>(
//                                 GunID::Sniper, nullptr, Vector2(), 0,
//                                 std::make_unique<Rectangle>(Vector2(), 0, 0), Vector2());
//                     }});
//     factory.insert({GunID::Helmet, []() {
//                         return std::make_unique<EquippableItem>(
//                                 GunID::Helmet, nullptr, Vector2(), 0,
//                                 std::make_unique<Rectangle>(Vector2(), 0, 0), Vector2());
//                     }});
//     factory.insert({GunID::Armor, []() {
//                         return std::make_unique<EquippableItem>(
//                                 GunID::Armor, nullptr, Vector2(), 0,
//                                 std::make_unique<Rectangle>(Vector2(), 0, 0), Vector2());
//                     }});
// }
// std::unique_ptr<EquippableItem> ItemFactory::createItem(GunID id) {
//     if (factory.empty()) {
//         inicializeFactory();
//     }
//     if (factory.find(id) == factory.end()) {
//         throw std::invalid_argument(INVALID_ID);
//     }
//     return factory.at(id)();
// }