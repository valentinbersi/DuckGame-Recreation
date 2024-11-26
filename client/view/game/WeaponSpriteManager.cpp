#include "WeaponSpriteManager.h"

#include <string>
#include <yaml-cpp/yaml.h>

#include "Spritesheet.h"

#define DEFAULT_SCALE 2.5f
#define EFFECT_PATH "assets/particles/Effect.png"
#define LASERFLARE_PATH "assets/particles/LaserFlare.png"
#define PLASMA_PATH "assets/particles/Plasma.png"

WeaponSpriteManager::WeaponSpriteManager() {}




// CAMBIAR FLIP POR EL USO DE STATE




void WeaponSpriteManager::drawWeapon(Spritesheet* spritesheet, SDL2pp::Rect& position,
                                     float scale, const DuckState& state) {
    draw(spritesheet, position, scale, state);

    if (state.isShooting) {
        spritesheet->selectSprite(0, 0, true);

        switch (state.gunEquipped) {
            case ItemID::CowboyPistol:
            case ItemID::Magnum:
            case ItemID::DuelPistol:
                drawEffect1(spritesheet, position, scale, state);
                break;
            case ItemID::Ak47:
            case ItemID::Sniper:
            case ItemID::Shotgun:
                drawEffect2(spritesheet, position, scale, state);
                break;
            case ItemID::LaserRifle:
                drawLaserFlare(spritesheet, position, scale, state);
                break;
            case ItemID::PewPewLaser:
                drawPlasma(spritesheet, position, scale, state);
                break;

            case ItemID::Grenade:
                break;
            case ItemID::Banana:
                break;
            default:
                break;
        }
    }
}

void WeaponSpriteManager::draw(Spritesheet* spritesheet, SDL2pp::Rect& position,
                               float scale, const DuckState& state) {
    spritesheet->selectSprite(0, 0, false);
    if (!state.lookingUp) {
        if (state.flipped)
            position.x -= 0.30 * scale;
        else
            position.x += 0.30 * scale;
        position.y -= 0.01 * scale;

    } else {
        if (state.flipped)
            position.x += 0.30 * scale;
        else
            position.x -= 0.30 * scale;
        position.y -= 0.40 * scale;
    }

    std::string path = gunPaths[state.gunEquipped];
    spritesheet->drawWeapon(position, state.flipped, path);
}

void WeaponSpriteManager::drawEffect1(Spritesheet* spritesheet, SDL2pp::Rect& position,
                                      float scale, const DuckState& state) {
    if (!state.lookingUp) {
        if (state.flipped)
            position.x -= 1.6 * scale;
        else
            position.x += 1.6 * scale;
        position.y -= 0.9 * scale;

    } else {
        if (state.flipped)
            position.x += 1.0 * scale;
        else
            position.x -= 1.0 * scale;
        position.y -= 1.6 * scale;
    }
    spritesheet->drawEffects(position, state.flipped, EFFECT_PATH);
}

void WeaponSpriteManager::drawEffect2(Spritesheet* spritesheet, SDL2pp::Rect& position,
                                      float scale, const DuckState& state) {
    if (!state.lookingUp) {
        if (state.flipped)
            position.x -= 2.0 * scale;
        else
            position.x += 2.0 * scale;
        position.y -= 0.9 * scale;

    } else {
        if (state.flipped)
            position.x += 0.8 * scale;
        else
            position.x -= 0.8 * scale;
        position.y -= 2.0 * scale;
    }
    spritesheet->drawEffects(position, state.flipped, EFFECT_PATH);
}

void WeaponSpriteManager::drawLaserFlare(Spritesheet* spritesheet, SDL2pp::Rect& position, float scale, const DuckState& state) {
    if (!state.lookingUp) {
        if (state.flipped)
            position.x -= 1.6 * scale;
        else
            position.x += 1.6 * scale;
        position.y -= 0.25 * scale;

    } else {
        if (state.flipped)
            position.x += 0.2 * scale;
        else
            position.x -= 0.2 * scale;
        position.y -= 1.6 * scale;
    }

    spritesheet->drawEffects(position, state.flipped, LASERFLARE_PATH);
}

void WeaponSpriteManager::drawPlasma(Spritesheet* spritesheet, SDL2pp::Rect& position,
                                     float scale, const DuckState& state) {
    if (!state.lookingUp) {
        if (state.flipped)
            position.x -= 1.8 * scale;
        else
            position.x += 1.8 * scale;
        position.y -= 0.3 * scale;

    } else {
        if (state.flipped)
            position.x += 0.2 * scale;
        else
            position.x -= 0.2 * scale;
        position.y -= 1.8 * scale;
    }
    spritesheet->drawEffects(position, state.flipped, PLASMA_PATH);
}
