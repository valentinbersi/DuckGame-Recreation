#pragma once

#include <list>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

#include "Vector2.h"
#include "DuckData.h"
#include "SpriteManager.h"
#include "Spritesheet.h"

class Camera {

public:
    Camera(int& windowWidth, int& WindowHeight);
    void update(std::list<std::unique_ptr<DuckData>>& ducks);
    void loadBackgroundSize(SDL2pp::Texture& backgroundTexture);
    SDL_Rect getViewRect();
    float getScale() const;
    int getBackgroundWidth() const;
    int getBackgroundHeight() const;

private:
    void calculateScale(std::list<std::unique_ptr<DuckData>>& ducks);
    float calculateMaxDistance(std::list<std::unique_ptr<DuckData>>& ducks);
    Vector2 centerOfDucks(std::list<std::unique_ptr<DuckData>>& ducks);
    //void adjustSpritePositions(std::list<std::unique_ptr<DuckData>>& ducks);

    int& windowWidth;
    int& windowHeight;
    int backgroundWidth;
    int backgroundHeight;
    float x;
    float y;
    float scale;
    float oldScale;
};
