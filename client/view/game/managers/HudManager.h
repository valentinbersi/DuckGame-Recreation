#pragma once

#include <list>
#include <memory>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2pp/SDL2pp.hh>

#include "DuckData.h"
#include "SpriteManager.h"

class HudManager {
public:
    HudManager(int& windowWidth, int& windowHeight, SDL2pp::Renderer& renderer, bool& transition,
               bool& roundFinished, bool& setFinished, bool& gameFinished);
    ~HudManager() = default;
    void check(std::list<DuckData>& ducks, std::list<DuckData>& ducksToRender,
               const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping);

private:
    void toBlackTransition(int centerX, int centerY) const;
    void winnerShow(std::list<DuckData>& ducksToRender,
                    const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping);
    void finishedRound() const;
    void finishedSet(std::list<DuckData>& ducks,
                     const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping);
    void finishedGame(std::list<DuckData>& ducks,
                      const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping);
    void showPoints(std::list<DuckData>& ducks, SDL2pp::Rect& tableRect,
                    const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping);
    void resetFlags() const;
    int& windowWidth;
    int& windowHeight;
    SDL2pp::Renderer& renderer;
    bool& transition;
    bool& roundFinished;
    bool& setFinished;
    bool& gameFinished;
};
