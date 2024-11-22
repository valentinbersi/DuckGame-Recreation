#pragma once

#include <exception>
#include <iostream>
#include <unordered_map>
#include <string>
#include <list>
#include <memory>
#include <vector>
#include <random>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/SDL2pp.hh>

#include "SpriteManager.h"
#include "Camera.h"
#include "Communicator.h"
#include "ServerMessage.h"
#include "SoundManager.h"
#include "GameStatus.h"
#include "DuckState.h"
#include "DuckData.h"
#include "MessageType.h"
#include "GameMessage.h"
#include "EventHandler.h"
#include "EnviromentRenderer.h"
#include "Vector2.h"
#include "Timer.h"

class Game {

public:
    Game(Communicator& communicator, bool& twoPlayersLocal);
    ~Game();

    void init();

private:
    void filterObjectsToRender();
    SDL2pp::Texture startBackground();
    std::unordered_map<DuckID, std::unique_ptr<SpriteManager>> createSpritesMapping();
    void updatePlayers(std::unordered_map<DuckID, std::unique_ptr<SpriteManager>>& spritesMapping);
    void updateBlocks(EnviromentRenderer& enviromentRenderer);
    void getSnapshot();
    void showBackground(SDL2pp::Texture& backgroundTexture);

    void clearObjects();
    //void typeOfObject2D(std::unique_ptr<GameObject2DData> gameObject2D);

    bool running;
    int window_width;
    int window_height;
    Communicator& communicator;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;
    SoundManager soundManager;
    Timer timer;
    //EnviromentRenderer enviromentRenderer;
    bool& twoPlayersLocal;
    Camera camera;

    std::list<DuckData> ducksToRender;
    std::list<SizedObjectData> blocksToRender;
    std::list<DuckData> ducks;
    std::list<SizedObjectData> blocks;

    std::vector<std::string> backgrounds = {
            "assets/background/forest-night.png",
            "assets/background/city.png",
            "assets/background/forest-day.png",
            "assets/background/snowy-peaks.png",
            "assets/background/desert.png"
    };
};
