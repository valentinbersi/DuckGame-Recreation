#pragma once

#include <algorithm>
#include <list>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

#include "Camera.h"
#include "DuckData.h"
#include "Rectangle.h"
#include "SpriteManager.h"
#include "Spritesheet.h"
#include "Vector2.h"

class Camera {
public:
    // Constructor.
    Camera(int& windowWidth, int& windowHeight);

    // Calculates the aspect ratio of the window, determines the center of all ducks,
    // and calculates the maximum distance between any two ducks. It then updates the zoom level
    // and view rectangle of the camera based on these values.
    void update(std::list<DuckData>& ducks, float deltaTime);

    // Returns the view rectangle of the camera.
    Rectangle& getViewRect();

private:
    // This method adjusts the size of the view rectangle based on the maximum distance between
    // ducks and the aspect ratio of the window. It then centers the view rectangle on the provided
    // center point.
    void updateZoom(const Vector2& center, const Vector2& maxDistance, float aspectRatio,
                    float deltaTime);

    // Calculates the maximum distance between any ducks in the list.
    static Vector2 calculateMaxDistance(std::list<DuckData>& ducks, float aspectRatio);

    // Calculates the center point of all ducks in the list.
    static Vector2 centerOfDucks(const std::list<DuckData>& ducks);

    int& windowWidth;
    int& windowHeight;
    Rectangle viewRect;
    bool ducksArrived;
};
