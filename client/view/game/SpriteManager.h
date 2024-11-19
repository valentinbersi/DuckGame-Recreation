#pragma once

#include <string>

#include "Spritesheet.h"
#include "DuckData.h"
#include <SDL2pp/SDL2pp.hh>

class SpriteManager {

public:
    // Constructor
    SpriteManager(const char* path1, const char* path2,
                  SDL2pp::Renderer& renderer, TextureManager& textureManager /*, int& window_width, int& window_height*/);

    // Destructor
    ~SpriteManager() = default;

    void update(bool playing_dead, bool crouching, bool in_air, bool flapping, bool being_damaged,
                bool moving_right, bool moving_left /*, bool armor, bool helmet*/);
    void updateEquipment(bool helmet, bool chestplate, GunID& gun);
    void draw(int col, int row);
    void updatePosition(float new_x, float new_y);
    void setScale(float newScale);

    Spritesheet& getSpritesheet();

private:
    void setFlags(bool in_air, bool flapping, bool moving_right, bool moving_left);
    void negateFlag(bool flag, bool& flagToNegate);
    void drawMainSprite(int col, int row);
    void drawFeathers(int col, int row, bool hasWeapon);
    void drawChestplate(int col, int row);
    void drawHelmet();
    void drawWeapon();
    SDL2pp::Rect getPosition(bool isFeather, bool isRightFeather, bool isChestPlate, bool isHelmet);
    SDL2pp::Rect calculateBasePosition();
    void adjustForFeathers(SDL2pp::Rect& position, bool isRightFeather);
    void adjustForHelmet(SDL2pp::Rect& position);

    const char* path1;
    const char* path2;
    float scale;
    bool moving_right;
    bool moving_left;
    bool in_air;
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
        {GunID::Granade, "path/to/granade.png"},
        {GunID::Banana, "path/to/banana.png"},
        {GunID::PewPewLaser, "path/to/pewpewlaser.png"},
        {GunID::LaserRifle, "path/to/laserrifle.png"},
        {GunID::Ak47, "path/to/ak47.png"},
        {GunID::DuelPistol, "path/to/duelpistol.png"},
        {GunID::CowboyPistol, "path/to/cowboypistol.png"},
        {GunID::Magnum, "path/to/magnum.png"},
        {GunID::Shotgun, "path/to/shotgun.png"},
        {GunID::Sniper, "path/to/sniper.png"},
    };
};
