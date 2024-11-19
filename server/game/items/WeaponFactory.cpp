#include "WeaponFactory.h"

// void WeaponFactory::inicializeFactory() {
//     //donde diga EquipableWeapon dependera del arma en si. las cualies heredan de EquipableWeapon
//     factory.insert({GunID::Granade, []() {
//                         return std::make_unique<EquippableWeapon>(GunID::Granade);
//                     }});
//     factory.insert({GunID::Banana, []() {
//                         return std::make_unique<EquippableWeapon>(GunID::Banana);
//                     }});
//     factory.insert({GunID::PewPewLaser, []() {
//                         return std::make_unique<EquippableWeapon>(GunID::PewPewLaser);
//                     }});
//     factory.insert({GunID::LaserRifle, []() {
//                         return std::make_unique<EquippableWeapon>(GunID::LaserRifle);
//                     }});
//     factory.insert({GunID::Ak47, []() {
//                         return std::make_unique<EquippableWeapon>(GunID::Ak47);
//                     }});
//     factory.insert({GunID::DuelPistol, []() {
//                         return std::make_unique<EquippableWeapon>(GunID::DuelPistol);
//                     }});
//     factory.insert({GunID::CowboyPistol, []() {
//                         return std::make_unique<EquippableWeapon>(GunID::CowboyPistol);
//                     }});
//     factory.insert({GunID::Magnum, []() {
//                         return std::make_unique<EquippableWeapon>(GunID::Magnum);
//                     }});
//     factory.insert({GunID::Shotgun, []() {
//                         return std::make_unique<EquippableWeapon>(GunID::Shotgun);
//                     }});
//     factory.insert({GunID::Sniper, []() {
//                         return std::make_unique<EquippableWeapon>(GunID::Sniper);
//                     }});
// }

// std::unique_ptr<EquippableWeapon> WeaponFactory::createItem(GunID id) {
//     if (factory.empty()) {
//         inicializeFactory();
//     } 
//     if (factory.find(id) != factory.end()) {
//         throw std::invalid_argument("invalid id");
//     }
//     return factory.at(id)();
// }


