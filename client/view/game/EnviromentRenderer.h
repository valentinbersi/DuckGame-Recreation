#pragma once

#include <list>

#include <SDL2pp/SDL2pp.hh>
#include "Vector2.h"

// class that renders all... besides ducks
class EnviromentRenderer {

public:
    // Constructor.
    explicit EnviromentRenderer(SDL2pp::Renderer& renderer);

    // Draws the environment texture at the specified position.
    void drawEnviroment(SDL2pp::Rect& position, const char* path) const;

    void drawBullets(const std::list<std::pair<Vector2, Vector2>>& bulletPositions) const;

private:
    SDL2pp::Renderer& renderer;
};
