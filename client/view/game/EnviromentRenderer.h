#pragma once

#include <list>

#include <SDL2pp/SDL2pp.hh>
#include "Vector2.h"

// class that renders all... besides ducks
class EnviromentRenderer {

public:
    // Constructor
    explicit EnviromentRenderer(SDL2pp::Renderer& renderer);

    /**
     * Draws the environment texture at the specified position
     * @param position: the position where the texture will be drawn
     * @param path: the path to the texture
     */
    void drawEnviroment(SDL2pp::Rect& position, const char* path) const;

    /**
     * Draws the bullets in the screen
     * @param bulletPositions: the positions of the bullets to be drawn
     */
    void drawBullets(const std::list<std::pair<Vector2, Vector2>>& bulletPositions) const;

private:
    SDL2pp::Renderer& renderer;
};
