#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2pp/SDL2pp.hh>

#include <list>
#include <memory>
#include "SpriteManager.h"
#include "DuckData.h"

class HudManager {
public:
    HudManager(int& windowWidth, int& windowHeight, SDL2pp::Renderer& renderer, bool& transition);
    ~HudManager() = default;
    void check(bool& roundFinished, bool& setFinished, bool& gameFinished, std::list<DuckData>& ducks, const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping, float delta);
    void finishedRound(float delta);

private:
    void finishedSet(std::list<DuckData>& ducks, const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping, float delta);
    void showPoints(std::list<DuckData>& ducks, SDL2pp::Rect& tableRect, const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping);
    void defaultValues();
    int& windowWidth;
    int& windowHeight;
    SDL2pp::Renderer& renderer;
    bool& transition;
    bool imageDisplayed;
    float timeElapsed;

    int size;
};
