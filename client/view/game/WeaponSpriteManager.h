#pragma once

#include <string>
#include <unordered_map>

#include "DuckState.h"
#include "ItemID.h"
#include "Spritesheet.h"
#include "TextureManager.h"

class WeaponSpriteManager {

public:
    // Constructor.
    WeaponSpriteManager();

    // Selects the weapon to be drawn and its effects based on the current state.
    void drawWeapon(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale,
                    const DuckState& state);

private:
    // Draws the main sprite of each weapon.
    void draw(Spritesheet* spritesheet, SDL2pp::Rect& position, float scale,
              const DuckState& state);

    // Draws the first type of effect of the weapons.
    void drawEffect1(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale, const DuckState& state);

    // Draws the second type of effect of the weapons.
    void drawEffect2(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale, const DuckState& state);

    // Draws the laser flare effect for the Laser Rifle.
    void drawLaserFlare(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale, const DuckState& state);

    // Draws the plasma effect for the Pew Pew Laser.
    void drawPlasma(Spritesheet* spritesheet, SDL2pp::Rect& position, bool flip, float scale, const DuckState& state);

    std::unordered_map<ItemID, std::string> gunPaths = {
            {ItemID::Grenade, "assets/weapons/Grenade.png"},
            {ItemID::Banana, "assets/weapons/Banana.png"},
            {ItemID::PewPewLaser, "assets/weapons/PewPewLaser.png"},
            {ItemID::LaserRifle, "assets/weapons/LaserRifle.png"},
            {ItemID::Ak47, "assets/weapons/Ak47.png"},
            {ItemID::DuelPistol, "assets/weapons/DuelPistol.png"},
            {ItemID::CowboyPistol, "assets/weapons/CowboyPistol.png"},
            {ItemID::Magnum, "assets/weapons/Magnum.png"},
            {ItemID::Shotgun, "assets/weapons/Shotgun.png"},
            {ItemID::Sniper, "assets/weapons/Sniper.png"},
    };
};
