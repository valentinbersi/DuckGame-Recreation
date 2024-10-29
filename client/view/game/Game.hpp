#pragma once

#include <exception>
#include <iostream>
#include <unordered_map>
#include <string>
#include <list>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/SDL2pp.hh>

#include "SpriteManager.h"
#include "../../comunicator/Communicator.h"
#include "../../protocol/ClientMessage.h"
#include "../../../common/game/GameStatus.hpp"
#include "../../../common/game/GameObjectData.h"
#include "../../../common/game/GameObject2DData.h"
#include "../../../common/game/DuckData.h"

#define greySheet "../../assets/sprites/duck/greyDuck.png"
#define orangeSheet "../../assets/sprites/duck/orangeDuck.png"
#define whiteSheet "../../assets/sprites/duck/whiteDuck.png"
#define yellowSheet "../../assets/sprites/duck/yellowDuck.png"

#define greyFeathers "../../assets/sprites/duck/greyDuckFeathers.png"
#define orangeFeathers "../../assets/sprites/duck/orangeDuckFeathers.png"
#define whiteFeathers "../../assets/sprites/duck/whiteDuckFeathers.png"
#define yellowFeathers "../../assets/sprites/duck/yellowDuckFeathers.png"

enum class Keybinds
{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ACTION,
    JUMP
};

class Game {

public:
    Game();
    ~Game();

    void init();

private:
    //void selectLevel();
    SDL2pp::Texture startBackground();
    Keybinds handleEvents();
    std::unordered_map<DuckID, SpriteManager>& createSpritesMapping(SDL2pp::Renderer& renderer);
    void updatePlayers(std::unordered_map<DuckID, SpriteManager>& spritesMapping);
    void getSnapshot();
    void showBackground(SDL2pp::Texture& backgroundTexture);

    void clearObjects();
    //void typeOfObject2D(std::unique_ptr<GameObject2DData> gameObject2D);

    bool running;
    int window_width;
    int window_height;
    Communicator communicator;
    Keybinds m_key;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;

    std::list<std::unique_ptr<DuckData>> ducks;
    //std::list<std::unique_ptr<GameObjectData>> objects;

    std::unordered_map<SDL_Scancode, Keybinds> keyMapping = {
        {SDL_SCANCODE_W, Keybinds::UP},
        {SDL_SCANCODE_S, Keybinds::DOWN},
        {SDL_SCANCODE_A, Keybinds::LEFT},
        {SDL_SCANCODE_D, Keybinds::RIGHT},
        {SDL_SCANCODE_E, Keybinds::ACTION},
        {SDL_SCANCODE_SPACE, Keybinds::JUMP}
    };

    /*std::unordered_map<int, std::string> levels {
        {1, "background1.png"},
        {2, "background2.png"},
        {3, "background3.png"},
        {4, "background4.png"},
        {5, "background5.png"},
        {6, "background6.png"},
        {7, "background7.png"},
        {8, "background8.png"},
    };*/

};
