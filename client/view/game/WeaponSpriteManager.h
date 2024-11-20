#pragma once

#include "GunID.h"
#include "DuckState.h"
#include "TextureManager.h"
#include "Spritesheet.h"

class WeaponSpriteManager {

public:
    WeaponSpriteManager();
    void drawWeapon(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale, const DuckState& state);
    void drawCowboyPistol(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale,
                          const DuckState& state);

private:
    std::unordered_map<GunID, std::string> gunPaths = {
        //{GunID::Granade, "../assets/weapons/"},
        //{GunID::Banana, "../assets/weapons/"},
        //{GunID::PewPewLaser, "../assets/weapons/"},
        //{GunID::LaserRifle, "../assets/weapons/"},
        //{GunID::Ak47, "../assets/weapons/"},
        //{GunID::DuelPistol, "../assets/weapons/"},
        {GunID::CowboyPistol, "assets/weapons/CowboyPistol.png"}
        //{GunID::Magnum, "../assets/weapons/"},
        //{GunID::Shotgun, "../assets/weapons/"},
        //{GunID::Sniper, "../assets/weapons/"},
    };
};
