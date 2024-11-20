#include "WeaponSpriteManager.h"

#include "Spritesheet.h"

#define DEFAULT_SCALE 2.5f

WeaponSpriteManager::WeaponSpriteManager() {}

void WeaponSpriteManager::drawWeapon(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale, const DuckState& state) {
    switch (state.gunEquipped) {
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
            drawCowboyPistol(spritesheet, position, flip, scale, state);
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

void WeaponSpriteManager::drawCowboyPistol(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale, const DuckState& state) {
    spritesheet->selectSprite(0, 0, false);
    if (flip)
        position.x -= (spritesheet->getClipWidth() / 2) + 2 * scale / DEFAULT_SCALE;
    else
        position.x += (spritesheet->getClipHeight() / 2) + 2 * scale / DEFAULT_SCALE;

    if (state.crouching)
        position.y += 20 * scale / DEFAULT_SCALE;
    else
        position.y += 8 * scale / DEFAULT_SCALE;

    std::string path = gunPaths[state.gunEquipped];
    spritesheet->drawWeapon(position, flip, path);

    if (state.isShooting) {
        spritesheet->selectSprite(0, 0, true);
        if (flip)
            position.x -= 33 * scale / DEFAULT_SCALE;
        else
            position.x += 74 * scale / DEFAULT_SCALE;

        position.y += 8 * scale / DEFAULT_SCALE;
        spritesheet->drawEffects(position, flip);
    }
}
