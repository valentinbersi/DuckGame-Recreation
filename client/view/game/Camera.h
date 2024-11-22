#pragma once

#include <algorithm>
#include <list>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

#include "Camera.h"
#include "DuckData.h"
#include "SpriteManager.h"
#include "Spritesheet.h"
#include "Vector2.h"
#include "Rectangle.h"

class Camera {

public:
    Camera(int& windowWidth, int& windowHeight);
    void update(std::list<DuckData>& ducks);
    //void loadBackgroundSize(SDL2pp::Texture& backgroundTexture);
    //float getScale() const;
    Rectangle& getViewRect();

private:
    void updateZoom(const Vector2& center, const Vector2& maxDistance);
    static Vector2 calculateMaxDistance(std::list<DuckData>& ducks);
    static Vector2 centerOfDucks(std::list<DuckData>& ducks);
    // void adjustSpritePositions(std::list<std::unique_ptr<DuckData>>& ducks);

    int& windowWidth;
    int& windowHeight;
    Rectangle viewRect;
    //float zoom;
};
