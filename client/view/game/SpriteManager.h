#pragma once

#include <string>

#include "Spritesheet.h"

class SpriteManager {

public:
    // Constructor
    SpriteManager(const char* path1, const char* path2, SDL2pp::Renderer& renderer/*, int& window_width, int& window_height*/);

    // Destructor
    ~SpriteManager() = default;

    void setFlags(bool in_air, bool flapping, bool moving_right, bool moving_left);
    void update(bool playing_dead, bool crouching, bool in_air, bool flapping, bool being_damaged,
                bool moving_right, bool moving_left);
    void draw(int col, int row);
    void updatePosition(float new_x, float new_y);

    // Initializes the position where the sprite will be drawn
    // void selectPosition(int c, int r);

    void incFrame();
    void incFlappingFrame();
    void changeActive();

private:
    void resetFrame();
    void resetFlappingFrame();
    void activateManager();
    void changeFlapping();
    SDL2pp::Rect getPosition(bool isFeather, bool isRightFeather);

    const char* path1;
    const char* path2;
    float scale;
    bool moving_right;
    bool moving_left;
    bool in_air;
    bool flapping;
    bool flip;

    Spritesheet spritesheet;

    // enum de types (de active). es decir, que tipo de animacion esta activa que tenga multiples
    // frame
    int frame;
    int flappingFrame;
    double m_position_x;
    double m_position_y;
};
