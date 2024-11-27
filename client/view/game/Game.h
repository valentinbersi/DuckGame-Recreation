#pragma once

#include <exception>
#include <iostream>
#include <list>
#include <memory>
#include <random>
#include <string>
#include <unordered_map>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2pp/SDL2pp.hh>

#include "Camera.h"
#include "Communicator.h"
#include "DuckData.h"
#include "HudManager.h"
#include "DuckState.h"
#include "EnviromentRenderer.h"
#include "EventHandler.h"
#include "GameMessage.h"
#include "GameStatus.h"
#include "MessageType.h"
#include "ServerMessage.h"
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
    // view, it would not be rendered.
    void filterObjectsToRender();

    // Starts the background randomly.
    SDL2pp::Texture startBackground();

    // Creates the mapping of the SpriteManagers for each duck.
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
    void updateBlocks(EnviromentRenderer& enviromentRenderer);

    /**
     * Updates the positions and scales of the weapon spawns based on the camera view and renders
     * @param enviromentRenderer the renderer that draws the enviroment objects
     */
    void updateItemSpawns(EnviromentRenderer& enviromentRenderer);

    /**
     * Updates the positions and scales of the items based on the camera view and renders
     * @param enviromentRenderer the renderer that draws the enviroment objects
     */
    void updateItems(EnviromentRenderer& enviromentRenderer);

    // Receives the latest game status snapshot from the server and updates the game objects.
    void getSnapshot();

    /**
    * Shows the background texture
    * @param backgroundTexture the background texture to show
    */
    void showBackground(SDL2pp::Texture& backgroundTexture);

    // Clears the game objects, expecting to refill them with the next snapshot.
    void clearObjects();

    void finishedSet();

    bool running;
    bool roundFinished;
    bool setFinished;
    bool gameFinished;
    bool transition;
    int window_width;
    int window_height;
    Communicator& communicator;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    SoundManager soundManager;
    Timer timer;
    bool& twoPlayersLocal;
    Camera camera;
    static const HashMap<ItemID, cppstring> weaponSprites;

    std::list<SizedObjectData> itemSpawns;
    std::list<SizedObjectData> itemSpawnsToRender;
    std::list<ItemData> items;
    std::list<ItemData> itemsToRender;
    std::list<SizedObjectData> blocks;
    std::list<SizedObjectData> blocksToRender;
    std::list<DuckData> ducks;  // No ducks to render because all ducks should be rendered

    std::vector<std::string> backgrounds = {
            "assets/background/forest-night.png", "assets/background/city.png",
            "assets/background/forest-day.png",   "assets/background/snowy-peaks.png",
            "assets/background/desert.png",       "assets/background/cascade-cave.png",
            "assets/background/sunset.png",       "assets/background/dark-cave.png"};
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
