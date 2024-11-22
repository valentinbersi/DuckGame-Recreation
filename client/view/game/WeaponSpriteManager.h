#pragma once

#include <string>
#include <unordered_map>

#include "DuckState.h"
#include "ItemID.h"
#include "Spritesheet.h"
#include "TextureManager.h"

class WeaponSpriteManager {

public:
    WeaponSpriteManager();
    void drawWeapon(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale,
                    const DuckState& state);

private:
    void draw(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale,
              const DuckState& state);
    void drawEffect1(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale);
    void drawEffect2(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale);
    void drawLaserFlare(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale);
    void drawPlasma(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale);

    std::unordered_map<ItemID, std::string> gunPaths = {
            {ItemID::Grenade, "assets/weapons/Grenade.png"},
            {ItemID::Banana, "assets/weapons/Banana.png"},
            {ItemID::PewPewLaser, "assets/weapons/PewPewLaser.png"},
            {ItemID::LaserRifle, "assets/weapons/LaserRifle.png"},
            {ItemID::Ak47, "assets/weapons/Ak47.png"},
            //{GunID::DuelPistol, "assets/weapons/DuelPistol.png"},
            {ItemID::CowboyPistol, "assets/weapons/CowboyPistol.png"},
            {ItemID::Magnum, "assets/weapons/Magnum.png"},
            {ItemID::Shotgun, "assets/weapons/Shotgun.png"},
            {ItemID::Sniper, "assets/weapons/Sniper.png"},
    };
};
