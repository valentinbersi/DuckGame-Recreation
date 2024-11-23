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
    std::unordered_map<DuckID, std::unique_ptr<SpriteManager>> createSpritesMapping();

    // Updates the positions, states, and scales of the player sprites based on the camera view.
    void updatePlayers(
            const std::unordered_map<DuckID, std::unique_ptr<SpriteManager>>& spritesMapping);

    // Updates the positions and scales of the blocks based on the camera view and renders them.
    void updateBlocks(EnviromentRenderer& enviromentRenderer);


    /**
     * Updates the positions and scales of the weapon spawns based on the camera view and renders
     * @param enviromentRenderer the renderer that draws the enviroment objects
     */
    void updateWeaponSpawns(EnviromentRenderer& enviromentRenderer);

    // Receives the latest game status snapshot from the server and updates the game objects.
    void getSnapshot();

    // Shows the background texture.
    void showBackground(SDL2pp::Texture& backgroundTexture);

    // Clears the game objects, expecting to refill them with the next snapshot.
    void clearObjects();

    bool running;
    int window_width;
    int window_height;
    Communicator& communicator;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    SoundManager soundManager;
    Timer timer;
    bool& twoPlayersLocal;
    Camera camera;

    std::list<SizedObjectData> itemSpawns;
    std::list<SizedObjectData> itemSpawnsToRender;
    std::list<SizedObjectData> blocks;
    std::list<SizedObjectData> blocksToRender;
    std::list<DuckData> ducks;  // No ducks to render because all ducks should be rendered

    std::vector<std::string> backgrounds = {
            "assets/background/forest-night.png", "assets/background/city.png",
            "assets/background/forest-day.png",   "assets/background/snowy-peaks.png",
            "assets/background/desert.png",       "assets/background/cascade-cave.png",
            "assets/background/sunset.png",       "assets/background/dark-cave.png"};
};
