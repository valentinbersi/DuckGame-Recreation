#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

#include "DuckData.h"
#include "DuckState.h"
#include "ItemID.h"
#include "Spritesheet.h"
#include "WeaponSpriteManager.h"


class SpriteManager {
public:
    // Constructor
    SpriteManager(const char* path1, const char* path2,
                  SDL2pp::Renderer& renderer /*, int& window_width, int& window_height*/);

    // Destructor
    ~SpriteManager() = default;

    // Updates the sprite manager based on the current state of the duck.
    // It then draws the appropriate sprite based on whether the duck is in the air, being damaged,
    // playing dead, crouching, or moving. This is done by calling the different draw methods.
    void update(const DuckState& state);

    // updates the state of the duck's helmet, chestplate and weapon based on the provided
    // parameters
    void updateEquipment(bool helmet, bool chestplate, ItemID& gun);

    // Ddraws the main sprite using the provided column and row indices.
    //  It then checks if the duck has a chestplate, helmet, or weapon equipped and draws them
    //  accordingly. Finally, it draws the feathers based on whether the duck has a weapon equipped.
    void draw(int col, int row, const DuckState& state);

    // Updates the position of the duck.
    void updatePosition(float new_x, float new_y);

    // Sets the scale of the sprite.
    void setScale(float newScale);

private:
    // Updates the internal flags of the SpriteManager based on the current state of the duck.
    void setFlags(const DuckState& state);

    // Negates the flagToNegate if it is different from the flag.
    void negateFlag(bool flag, bool& flagToNegate);

    // Draws the main sprite using the provided column and row indices.
    void drawMainSprite(int col, int row);

    // Draws the feathers based on the provided column and row indices and whether the duck has a
    // weapon equipped. Also it checks a lot of other flags.
    void drawFeathers(int col, int row, bool hasWeapon);

    // Draws the chestplate based on the provided column and row indices.
    // Also it checks other flags.
    void drawChestplate(int col, int row);

    // Draws the helmet.
    // Also it checks other flags.
    void drawHelmet();

    // Returns the position of the sprite based on the provided flags.
    SDL2pp::Rect getPosition(bool isFeather, bool isRightFeather, bool isChestPlate, bool isHelmet);

    // Returns the base position of the sprite based on the current position of the duck.
    // Meaning... this is the position of the duck and only the duck.
    SDL2pp::Rect calculateBasePosition();

    // Adjusts the position of the sprite for the feathers.
    void adjustForFeathers(SDL2pp::Rect& position, bool isRightFeather);

    // Adjusts the position of the sprite for the helmet.
    void adjustForHelmet(SDL2pp::Rect& position);

    // Adjusts the position of the sprite for the chestplate.
    void adjustForChestplate(SDL2pp::Rect& position);


    const char* path1;
    const char* path2;
    float scale;
    bool movingRight;
    bool movingLeft;
    bool inAir;
    bool crouching;
    bool flapping;
    bool flip;
    bool hasHelmet;
    bool hasChestplate;
    bool shooting;
    ItemID gunEquipped;
    std::unique_ptr<Spritesheet> spritesheet;
    std::unique_ptr<WeaponSpriteManager> weaponSpriteManager;
    int frame;
    int flappingFrame;
    double m_position_x;
    double m_position_y;
};
