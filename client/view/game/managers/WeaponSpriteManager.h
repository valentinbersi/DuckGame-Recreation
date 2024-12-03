#pragma once

#include <string>
#include <unordered_map>

#include "DuckState.h"
#include "ItemID.h"
#include "Resource.h"
#include "Spritesheet.h"
#include "TextureManager.h"

class WeaponSpriteManager {

public:
    // Constructor
    WeaponSpriteManager();

    /**
     * Selects the weapon to be drawn and its effects based on the current state
     * @param spritesheet The spritesheet that'll draw the weapon
     * @param position The position to draw the weapon at
     * @param scale The scale to draw the weapon at
     * @parm state The current state of the duck
     */
    void drawWeapon(Spritesheet* spritesheet, SDL2pp::Rect& position, float scale,
                    const DuckState& state);

private:
    // Draws the main sprite of each weapon
    void draw(Spritesheet* spritesheet, SDL2pp::Rect& position, float scale,
              const DuckState& state);

    // Draws the first type of effect of the weapons
    void drawEffect1(Spritesheet* spritesheet, SDL2pp::Rect& position, float scale,
                     const DuckState& state);

    // Draws the second type of effect of the weapons
    void drawEffect2(Spritesheet* spritesheet, SDL2pp::Rect& position, float scale,
                     const DuckState& state);

    // Draws the laser flare effect for the Laser Rifle
    void drawLaserFlare(Spritesheet* spritesheet, SDL2pp::Rect& position, float scale,
                        const DuckState& state);

    // Draws the plasma effect for the Pew Pew Laser
    void drawPlasma(Spritesheet* spritesheet, SDL2pp::Rect& position, float scale,
                    const DuckState& state);

    std::unordered_map<ItemID, std::string> gunPaths = {
            {ItemID::Grenade, Resource::get().resource("weapons/Grenade.png")},
            {ItemID::Banana, Resource::get().resource("weapons/Banana.png")},
            {ItemID::PewPewLaser, Resource::get().resource("weapons/PewPewLaser.png")},
            {ItemID::LaserRifle, Resource::get().resource("weapons/LaserRifle.png")},
            {ItemID::Ak47, Resource::get().resource("weapons/Ak47.png")},
            {ItemID::DuelPistol, Resource::get().resource("weapons/DuelPistol.png")},
            {ItemID::CowboyPistol, Resource::get().resource("weapons/CowboyPistol.png")},
            {ItemID::Magnum, Resource::get().resource("weapons/Magnum.png")},
            {ItemID::Shotgun, Resource::get().resource("weapons/Shotgun.png")},
            {ItemID::Sniper, Resource::get().resource("weapons/Sniper.png")},
            {ItemID::Helmet, Resource::get().resource("weapons/Helmet.png")},
            {ItemID::Armor, Resource::get().resource("weapons/Chestplate.png")},
    };
};
