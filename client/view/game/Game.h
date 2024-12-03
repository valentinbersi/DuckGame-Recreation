#pragma once

#include <list>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2pp/SDL2pp.hh>

#include "Camera.h"
#include "Communicator.h"
#include "Background.h"
#include "DuckData.h"
#include "EnviromentRenderer.h"
#include "GameStatus.h"
#include "SoundManager.h"
#include "SpriteManager.h"
#include "Timer.h"
#include "Vector2.h"

class Game {

public:
    // Constructor.
    Game(Communicator& communicator, bool& twoPlayersLocal);

    // Destructor.
    ~Game();

    // Main loop.
    void init();

private:
    // Filters the objects to render, based on the camera view. If the object is not in the camera
    // view, it would not be rendered
    void filterObjectsToRender();

    // Creates the mapping of the SpriteManagers for each duck
    std::unordered_map<DuckData::Id, std::unique_ptr<SpriteManager>> createSpritesMapping();

    /**
     * Updates the positions, states, and scales of the player sprites based on the camera view.
     * @param spritesMapping the mapping of the SpriteManager for each duck
     */
    void updatePlayers(
            const std::unordered_map<DuckData::Id, std::unique_ptr<SpriteManager>>& spritesMapping);

    /**
     * Updates the positions and scales of the objects given objects in the game
     * @param objects the objects to update
     * @tparam SizedObject the type of the objects, must me a SizedObject or a subclass of it
     * @return a list of the positions and sizes of the objects
     */
    template <typename SizedObject>
    std::list<SDL2pp::Rect> calculateObjectsPositionsAndSize(std::list<SizedObject> objects);

    /**
     * Updates the positions and scales of the blocks based on the camera view and renders them.
     * @param enviromentRenderer the renderer that draws the enviroment objects
     * @return
     */
    void updateBlocks(const EnviromentRenderer& enviromentRenderer);

    /**
     * Updates the positions and scales of the weapon spawns based on the camera view and renders
     * @param enviromentRenderer the renderer that draws the enviroment objects
     */
    void updateItemSpawns(const EnviromentRenderer& enviromentRenderer);

    /**
     * Updates the positions and scales of the boxes based on the camera view and renders
     * @param enviromentRenderer the renderer that draws the enviroment objects
     */
    void updateBoxes(const EnviromentRenderer& enviromentRenderer);

    /**
     * Updates the positions and scales of the items based on the camera view and renders
     * @param enviromentRenderer the renderer that draws the enviroment objects
     */
    void updateItems(const EnviromentRenderer& enviromentRenderer);

    /**
     * Updates the positions and scales of the ducks based on the camera view and renders
     * @param enviromentRenderer the renderer that draws the enviroment objects
     */
    void updateEffects(const EnviromentRenderer& enviromentRenderer);

    /**
     * Updates the positions and scales of the ducks based on the camera view and renders
     * @param segments the segments to update
     * @return a list of the positions and sizes of the segments
     */
    std::list<std::pair<Vector2, Vector2>> calculateSegmentPositionsAndSize(
            std::list<Segment2D>& segments);

    // Receives the latest game status snapshot from the server and updates the game objects
    void getSnapshot();

    // Shows the background texture received from the server
    void showBackground();

    // Clears the game objects, expecting to refill them with the next snapshot
    void clearObjects();

    bool running;
    bool roundFinished;
    bool setFinished;
    bool gameFinished;
    bool transition;
    bool explosion;
    int window_width;
    int window_height;
    Communicator& communicator;
    BackgroundID backgroundID;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    SoundManager soundManager;
    Timer timer;
    bool& twoPlayersLocal;
    Camera camera;
    static const HashMap<ItemID, std::string> weaponSprites;

    std::list<SizedObjectData> itemSpawns;
    std::list<SizedObjectData> itemSpawnsToRender;
    std::list<ItemData> items;
    std::list<ItemData> itemsToRender;
    std::list<SizedObjectData> blocks;
    std::list<SizedObjectData> blocksToRender;
    std::list<SizedObjectData> boxes;
    std::list<SizedObjectData> boxesToRender;
    std::list<SizedObjectData> impacts;
    std::list<std::list<Segment2D>> bulletPositions;
    std::list<SizedObjectData> explosions;
    std::list<DuckData> ducks;
    std::list<DuckData> ducksToRender;
};

template <typename SizedObject>
std::list<SDL2pp::Rect> Game::calculateObjectsPositionsAndSize(std::list<SizedObject> objects) {
    static_assert(std::is_base_of_v<SizedObjectData, SizedObject>,
                  "SizedObject must be a subclass of SizedObjectData");

    std::list<SDL2pp::Rect> rectsToDraw;

    for (SizedObjectData& object: objects) {
        const float objectCameraSize =
                camera.getViewRect().size().x() / object.rectangle.size().x();
        const float scale = static_cast<float>(window_width) / objectCameraSize;
        const float relativePositionX = object.position.x() - camera.getViewRect().center().x();
        const float relativePositionY = object.position.y() - camera.getViewRect().center().y();
        const float positionScaleX =
                static_cast<float>(window_width) / camera.getViewRect().size().x();
        const float positionScaleY =
                static_cast<float>(window_height) / camera.getViewRect().size().y();
        const float screenPositionX =
                relativePositionX * positionScaleX + static_cast<float>(window_width) / 2;
        const float screenPositionY =
                relativePositionY * positionScaleY + static_cast<float>(window_height) / 2;

        rectsToDraw.emplace_back(static_cast<i32>(screenPositionX - scale / 2),
                                 static_cast<i32>(screenPositionY - scale / 2),
                                 static_cast<i32>(scale), static_cast<i32>(scale));
    }

    return rectsToDraw;
}
