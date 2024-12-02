#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

#include "TextureManager.h"
#include <list>
#include "Vector2.h"

// class that renders all... besides ducks
class EnviromentRenderer {

public:
    // Constructor.
    explicit EnviromentRenderer(SDL2pp::Renderer& renderer);

    // Draws the environment texture at the specified position.
    void drawEnviroment(SDL2pp::Rect& position, const char* path);

    void drawBullets(const std::list<std::pair<Vector2, Vector2>>& bulletPositions);

private:
    SDL2pp::Renderer& renderer;
};
