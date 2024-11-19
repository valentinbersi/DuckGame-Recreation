#pragma once

#include <string>

#include "Spritesheet.h"
#include "DuckData.h"
#include "DuckState.h"
#include "GunID.h"
#include <SDL2pp/SDL2pp.hh>

class SpriteManager {

public:
    // Constructor
    SpriteManager(const char* path1, const char* path2,
                  SDL2pp::Renderer& renderer, TextureManager& textureManager /*, int& window_width, int& window_height*/);

    // Destructor
    ~SpriteManager() = default;

    void update(const DuckState& state);
    void updateEquipment(bool helmet, bool chestplate/*, GunID& gun*/);
    void draw(int col, int row);
    void updatePosition(float new_x, float new_y);
    void setScale(float newScale);

    Spritesheet& getSpritesheet();

private:
    void setFlags(const DuckState& state);
    void negateFlag(bool flag, bool& flagToNegate);
    void drawMainSprite(int col, int row);
    void drawFeathers(int col, int row, bool hasWeapon);
    void drawChestplate(int col, int row);
    void drawHelmet();
    void drawWeapon();
    SDL2pp::Rect getPosition(bool isFeather, bool isRightFeather, bool isChestPlate, bool isHelmet, bool isWeapon);
    SDL2pp::Rect calculateBasePosition();
    void adjustForFeathers(SDL2pp::Rect& position, bool isRightFeather);
    void adjustForHelmet(SDL2pp::Rect& position);
    void adjustForWeapon(SDL2pp::Rect& position);

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
    GunID gunEquipped;
    std::unique_ptr<Spritesheet> spritesheet;
    int frame;
    int flappingFrame;
    double m_position_x;
    double m_position_y;

    std::unordered_map<GunID, std::string> gunPaths = {
        //{GunID::Granade, "../assets/weapons/"},
        //{GunID::Banana, "../assets/weapons/"},
        //{GunID::PewPewLaser, "../assets/weapons/"},
        //{GunID::LaserRifle, "../assets/weapons/"},
        //{GunID::Ak47, "../assets/weapons/"},
        //{GunID::DuelPistol, "../assets/weapons/"},
        {GunID::CowboyPistol, "../assets/weapons/CowboyPistol.png"}
        //{GunID::Magnum, "../assets/weapons/"},
        //{GunID::Shotgun, "../assets/weapons/"},
        //{GunID::Sniper, "../assets/weapons/"},
    };
};
