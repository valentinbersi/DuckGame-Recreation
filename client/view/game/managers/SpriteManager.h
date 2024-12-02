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
    SpriteManager(std::string path1, std::string path2,
                  SDL2pp::Renderer& renderer /*, int& window_width, int& window_height*/);

    // Destructor
    ~SpriteManager() = default;

    // Updates the sprite manager based on the current state of the duck.
    // It then draws the appropriate sprite based on whether the duck is in the air, being damaged,
    // playing dead, crouching, or moving. This is done by calling the different draw methods.
    void update(const DuckState& state);

    // Ddraws the main sprite using the provided column and row indices.
    //  It then checks if the duck has a chestplate, helmet, or weapon equipped and draws them
    //  accordingly. Finally, it draws the feathers based on whether the duck has a weapon equipped.
    void draw(int col, int row);

    void drawWin(bool endGame);

    // Updates the position of the duck.
    void updatePosition(float new_x, float new_y);

    // Sets the scale of the sprite.
    void setScale(float newScale);

    DuckState& getState();

private:
    // Updates the internal flags of the SpriteManager based on the current state of the duck.
    void setFlags();

    // Negates the flagToNegate if it is different from the flag.
    void negateFlag(bool flag, bool& flagToNegate);

    // Draws the main sprite using the provided column and row indices.
    void drawMainSprite(int col, int row);

    // Draws the feathers based on the provided column and row indices and whether the duck has a
    // weapon equipped. Also it checks a lot of other flags.
    void drawFeathers(int col, int row);

    void drawFlapping();

    // Draws the chestplate based on the provided column and row indices.
    // Also it checks other flags.
    void drawChestplate(int col, int row);

    // Draws the helmet.
    // Also it checks other flags.
    void drawHelmet();

    // Returns the position of the sprite based on the provided flags.
    SDL2pp::Rect getPosition(bool isFeather, bool isChestPlate, bool isHelmet);

    // Returns the base position of the sprite based on the current position of the duck.
    // Meaning... this is the position of the duck and only the duck.
    SDL2pp::Rect calculateBasePosition();

    // Adjusts the position of the sprite for the feathers.
    void adjustForFeathers(SDL2pp::Rect& position);

    // Adjusts the position of the sprite for the helmet.
    void adjustForHelmet(SDL2pp::Rect& position);

    // Adjusts the position of the sprite for the chestplate.
    void adjustForChestplate(SDL2pp::Rect& position);


    std::string path1;
    std::string path2;
    float scale;
    bool isMoving;
    bool inAir;
    bool flapping;
    bool dead;
    std::unique_ptr<Spritesheet> spritesheet;
    std::unique_ptr<WeaponSpriteManager> weaponSpriteManager;
    DuckState state;
    int frame;
    int flappingFrame;
    double m_position_x;
    double m_position_y;
};
