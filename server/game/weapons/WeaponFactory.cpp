#include "WeaponFactory.h"
#define INVALID_ID "Invalid GunID"

std::unique_ptr<Weapon> WeaponFactory::inicializeFactory() {
    factory.insert({GunID::Granade, []() {
                        return std::make_unique<Weapon>(
                                GunID::Granade, nullptr, Vector2(0, 0), 0,
                                std::make_unique<Rectangle>(Vector2(0, 0), 0, 0), Vector2(0, 0));
                    }});
    factory.insert({GunID::Banana, []() {
                        return std::make_unique<Weapon>(
                                GunID::Banana, nullptr, Vector2(0, 0), 0,
                                std::make_unique<Rectangle>(Vector2(0, 0), 0, 0), Vector2(0, 0));
                    }});
    factory.insert({GunID::PewPewLaser, []() {
                        return std::make_unique<Weapon>(
                                GunID::PewPewLaser, nullptr, Vector2(0, 0), 0,
                                std::make_unique<Rectangle>(Vector2(0, 0), 0, 0), Vector2(0, 0));
                    }});
    factory.insert({GunID::LaserRifle, []() {
                        return std::make_unique<Weapon>(
                                GunID::LaserRifle, nullptr, Vector2(0, 0), 0,
                                std::make_unique<Rectangle>(Vector2(0, 0), 0, 0), Vector2(0, 0));
                    }});
    factory.insert({GunID::Ak47, []() {
                        return std::make_unique<Weapon>(
                                GunID::Ak47, nullptr, Vector2(0, 0), 0,
                                std::make_unique<Rectangle>(Vector2(0, 0), 0, 0), Vector2(0, 0));
                    }});
    factory.insert({GunID::DuelPistol, []() {
                        return std::make_unique<Weapon>(
                                GunID::DuelPistol, nullptr, Vector2(0, 0), 0,
                                std::make_unique<Rectangle>(Vector2(0, 0), 0, 0), Vector2(0, 0));
                    }});
    factory.insert({GunID::CowboyPistol, []() {
                        return std::make_unique<Weapon>(
                                GunID::CowboyPistol, nullptr, Vector2(0, 0), 0,
                                std::make_unique<Rectangle>(Vector2(0, 0), 0, 0), Vector2(0, 0));
                    }});
    factory.insert({GunID::Magnum, []() {
                        return std::make_unique<Weapon>(
                                GunID::Magnum, nullptr, Vector2(0, 0), 0,
                                std::make_unique<Rectangle>(Vector2(0, 0), 0, 0), Vector2(0, 0));
                    }});
    factory.insert({GunID::Shotgun, []() {
                        return std::make_unique<Weapon>(
                                GunID::Shotgun, nullptr, Vector2(0, 0), 0,
                                std::make_unique<Rectangle>(Vector2(0, 0), 0, 0), Vector2(0, 0));
                    }});
    factory.insert({GunID::Sniper, []() {
                        return std::make_unique<Weapon>(
                                GunID::Sniper, nullptr, Vector2(0, 0), 0,
                                std::make_unique<Rectangle>(Vector2(0, 0), 0, 0), Vector2(0, 0));
                    }});
}
std::unique_ptr<Weapon> WeaponFactory::createWeapon(GunID id) {
    if (factory.empty()) {
        inicializeFactory();
    }
    if (factory.find(id) != factory.end()) {
        return factory.at(id)();
    }
    throw std::invalid_argument(INVALID_ID);
}