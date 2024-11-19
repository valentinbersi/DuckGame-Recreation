#include "WeaponSpriteManager.h"

WeaponSpriteManager::WeaponSpriteManager() {}

void WeaponSpriteManager::drawWeapon(GunID& id) {
    switch (id) {
        case GunID::Grenade:
            // draw pistol
            break;
        case GunID::Banana:
            // draw shotgun
            break;
        case GunID::PewPewLaser:
            // draw machinegun
            break;
        case GunID::LaserRifle:
            // draw sniper
            break;
        case GunID::Ak47:
            // draw Ak47
            break;
        case GunID::DuelPistol:
            // draw DuelPistol
            break;
        case GunID::CowboyPistol:
            // draw CowboyPistol
            break;
        case GunID::Magnum:
            // draw Magnum
            break;
        case GunID::Shotgun:
            // draw Shotgun
            break;
        case GunID::Sniper:
            // draw Sniper
            break;
        default:
            // draw nothing
            break;
    }
}