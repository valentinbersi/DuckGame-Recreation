#pragma once

#include "Spritesheet.h"

// offsets in rows

enum class Keybinds
{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ACTION,
    JUMP
};

class Player {

public:
    Player(const char* path, int row, int column, SDL2pp::Renderer& renderer, int window_width, int window_height);
    ~Player();

    void start();
    void update(double delta_time, Keybinds m_key);

private:
    float scale;
    bool flip;
    double m_position_x;
    double m_position_y;
    int m_spritesheet_column;
    int window_width;
    int window_height;
    SDL2pp::Renderer& renderer;
    Spritesheet spritesheet;

    SDL2pp::Rect getPosition();

};
