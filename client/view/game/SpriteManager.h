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
    SpriteManager(const char* path1, const char* path2, SDL2pp::Renderer& renderer /*, int& window_width, int& window_height*/);

    // Destructor
    ~SpriteManager() = default;

    void update(const DuckState& state);
    void updateEquipment(bool helmet, bool chestplate /*, GunID& gun*/);
    void draw(int col, int row, const DuckState& state);
    void updatePosition(float new_x, float new_y);
    void setScale(float newScale);

private:
    void setFlags(const DuckState& state);
    void negateFlag(bool flag, bool& flagToNegate);
    void drawMainSprite(int col, int row);
    void drawFeathers(int col, int row, bool hasWeapon);
    void drawChestplate(int col, int row);
    void drawHelmet();
    SDL2pp::Rect getPosition(bool isFeather, bool isRightFeather, bool isChestPlate, bool isHelmet);
    SDL2pp::Rect calculateBasePosition();
    void adjustForFeathers(SDL2pp::Rect& position, bool isRightFeather);
    void adjustForHelmet(SDL2pp::Rect& position);

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
