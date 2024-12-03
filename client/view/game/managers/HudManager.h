#pragma once

#include <list>
#include <memory>
#include <SDL2pp/SDL2pp.hh>

#include "DuckData.h"
#include "SpriteManager.h"

class HudManager {
public:
    // Constructor
    HudManager(int& windowWidth, int& windowHeight, SDL2pp::Renderer& renderer, bool& transition,
               bool& roundFinished, bool& setFinished, bool& gameFinished);

    // Destructor
    ~HudManager() = default;

    /**
     * Checks if a transition is needed (if a round, set or game is finished)
     * @param ducks list of ducks
     * @param ducksToRender list of ducks to render
     * @param spritesMapping mapping of duck id to sprite manager to draw and adjust things
     */
    void check(std::list<DuckData>& ducks, std::list<DuckData>& ducksToRender,
               const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping);

private:
    /**
     * Shows a black transition
     * @param centerX centerX of the screen
     * @param centerY centerY of the screen
     */
    void toBlackTransition(int centerX, int centerY) const;

    /**
     * Shows a little crown or trophy in the head of the winner
     * @param ducksToRender list of ducks to render (it'll only have the winner)
     * @param spritesMapping mapping of duck id to sprite manager to draw and adjust things
     */
    void winnerShow(const std::list<DuckData>& ducksToRender,
                    const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping) const;

    // Shows the transition of a finished round and puts the loading screen
    void finishedRound() const;

    /**
     * Shows the finishedSet image and points of the ducks in the screen
     * @param ducks list of ducks
     * @param spritesMapping mapping of duck id to sprite manager to draw and adjust things
     */
    void finishedSet(std::list<DuckData>& ducks,
                     const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping);

    /**
     * Shows the finishedGame image and points of the ducks in the screen
     * @param ducks
     * @param spritesMapping
     */
    void finishedGame(std::list<DuckData>& ducks,
                      const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping);

    /**
     * Shows the points of the ducks in the screen
     * @param ducks list of ducks
     * @param tableRect rectangle of the table
     * @param spritesMapping mapping of duck id to sprite manager to draw and adjust things
     */
    void showPoints(const std::list<DuckData>& ducks, const SDL2pp::Rect& tableRect,
                    const HashMap<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping);

    // Sets the 'roundFinished' and 'setFinished' flags to false
    void resetFlags() const;

    int& windowWidth;
    int& windowHeight;
    SDL2pp::Renderer& renderer;
    bool& transition;
    bool& roundFinished;
    bool& setFinished;
    bool& gameFinished;
};
