#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

class Camera {

public:
    Camera(int& windowWidth, int& WindowHeight);
    void update(float targetX, float targetY);
    void loadBackgroundSize(SDL2pp::Texture& backgroundTexture);
    SDL_Rect getViewRect();

private:
    int windowWidth;
    int windowHeight;
    int backgroundWidth;
    int backgroundHeight;
    float x;
    float y;
};



