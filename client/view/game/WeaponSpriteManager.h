#pragma once

#include "GunID.h"
#include "DuckState.h"
#include "TextureManager.h"
#include "Spritesheet.h"

class WeaponSpriteManager {

public:
    WeaponSpriteManager();
    void drawWeapon(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale, const DuckState& state);

private:
    void draw(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale,
                      const DuckState& state);
    void drawEffect1(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale);
    void drawEffect2(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale);
    void drawLaserFlare(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale);
    void drawPlasma(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale);

    std::unordered_map<GunID, std::string> gunPaths = {
        {GunID::Grenade, "assets/weapons/Grenade.png"},
        {GunID::Banana, "assets/weapons/Banana.png"},
        {GunID::PewPewLaser, "assets/weapons/PewPewLaser.png"},
        {GunID::LaserRifle, "assets/weapons/LaserRifle.png"},
        {GunID::Ak47, "assets/weapons/Ak47.png"},
        //{GunID::DuelPistol, "assets/weapons/DuelPistol.png"},
        {GunID::CowboyPistol, "assets/weapons/CowboyPistol.png"},
        {GunID::Magnum, "assets/weapons/Magnum.png"},
        {GunID::Shotgun, "assets/weapons/Shotgun.png"},
        {GunID::Sniper, "assets/weapons/Sniper.png"},
    };
};
