#include "WeaponSpriteManager.h"

#include "Spritesheet.h"

#define DEFAULT_SCALE 2.5f
#define EFFECT_PATH "assets/particles/Effect.png"
#define LASERFLARE_PATH "assets/particles/LaserFlare.png"
#define PLASMA_PATH "assets/particles/Plasma.png"

WeaponSpriteManager::WeaponSpriteManager() {}

void WeaponSpriteManager::drawWeapon(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale, const DuckState& state) {
    draw(spritesheet, position, flip, scale, state);

    if (state.isShooting) {
        spritesheet->selectSprite(0, 0, true);

        switch (state.gunEquipped) {
            case ItemID::CowboyPistol:
            case ItemID::Magnum:
                drawEffect1(spritesheet, position, flip, scale);
                break;
            case ItemID::Ak47:
            case ItemID::Sniper:
            case ItemID::Shotgun:
                drawEffect2(spritesheet, position, flip, scale);
                break;
            case ItemID::LaserRifle:
                drawLaserFlare(spritesheet, position, flip, scale);
                break;
            case ItemID::PewPewLaser:
                drawPlasma(spritesheet, position, flip, scale);
                break;

            case ItemID::Grenade:
                // draw pistol
                    break;
            case ItemID::Banana:
                // draw shotgun
                    break;
            case ItemID::DuelPistol:
                // draw DuelPistol
                break;
            default:
                    break;
        }
    }
}

void WeaponSpriteManager::draw(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale, const DuckState& state) {
    spritesheet->selectSprite(0, 0, false);
    if (flip)
        position.x -= 3 * scale / DEFAULT_SCALE;
    else
        position.x += 3 * scale / DEFAULT_SCALE;

    if (state.crouching)
        position.y += 4 * scale / DEFAULT_SCALE;
    else
        position.y += 2 * scale / DEFAULT_SCALE;

    std::string path = gunPaths[state.gunEquipped];
    spritesheet->drawWeapon(position, flip, path);
}

void WeaponSpriteManager::drawEffect1(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale) {
    if (flip)
        position.x -= 17 * scale / DEFAULT_SCALE;
    else
        position.x += 17 * scale / DEFAULT_SCALE;

    position.y -= 8 * scale / DEFAULT_SCALE;
    spritesheet->drawEffects(position, flip, EFFECT_PATH);
}

void WeaponSpriteManager::drawEffect2(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale) {
    if (flip)
        position.x -= 19 * scale / DEFAULT_SCALE;
    else
        position.x += 19 * scale / DEFAULT_SCALE;

    position.y -= 9 * scale / DEFAULT_SCALE;
    spritesheet->drawEffects(position, flip, EFFECT_PATH);
}

void WeaponSpriteManager::drawLaserFlare(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale) {
    if (flip)
        position.x -= 17 * scale / DEFAULT_SCALE;
    else
        position.x += 17 * scale / DEFAULT_SCALE;

    position.y -= 2.5 * scale / DEFAULT_SCALE;
    spritesheet->drawEffects(position, flip, LASERFLARE_PATH);
}

void WeaponSpriteManager::drawPlasma(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale) {
    if (flip)
        position.x -= 17 * scale / DEFAULT_SCALE;
    else
        position.x += 17 * scale / DEFAULT_SCALE;

    position.y -= 3 * scale / DEFAULT_SCALE;
    spritesheet->drawEffects(position, flip, PLASMA_PATH);
}
