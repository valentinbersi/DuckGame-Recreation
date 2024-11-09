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
#include "Camera.h"
#include "Communicator.h"
#include "ServerMessage.h"
#include "GameStatus.h"
#include "GameObjectData.h"
#include "GameObject2DData.h"
#include "DuckData.h"
#include "MessageType.h"
#include "GameMessage.h"

class Game {

public:
    Game(Communicator& communicator, bool& twoPlayersLocal);
    ~Game();

    void init();

private:
    //void selectLevel();
    bool isFullscreen(SDL2pp::Window& window);
    void setFullscreen(bool fullscreen);
    SDL2pp::Texture startBackground();
    void handleEvents(std::unordered_map<DuckID, std::unique_ptr<SpriteManager>>& spritesMapping);
    void handleScreenEvents(SDL_Event& event, bool isKeyDown, SDL_Scancode& scancode, std::unordered_map<DuckID, std::unique_ptr<SpriteManager>>& spritesMapping);
    void handleKeyEvent(const SDL_Scancode& scancode, bool isKeyDown);
    std::unordered_map<DuckID, std::unique_ptr<SpriteManager>> createSpritesMapping();
    void updatePlayers(std::unordered_map<DuckID, std::unique_ptr<SpriteManager>>& spritesMapping, float currentScale);
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
    bool& twoPlayersLocal;
    Camera camera;

    std::list<std::unique_ptr<DuckData>> ducks;
    //std::list<std::unique_ptr<GameObjectData>> objects;

    std::unordered_map<SDL_Scancode, InputAction> keyMappingPressed = {
        {SDL_SCANCODE_W, InputAction::UP_PRESSED},
        {SDL_SCANCODE_S, InputAction::DOWN_PRESSED},
        {SDL_SCANCODE_A, InputAction::LEFT_PRESSED},
        {SDL_SCANCODE_D, InputAction::RIGHT_PRESSED},
        {SDL_SCANCODE_E, InputAction::ACTION_PRESSED},
        {SDL_SCANCODE_SPACE, InputAction::JUMP_PRESSED}
    };

    std::unordered_map<SDL_Scancode, InputAction> keyMappingReleased = {
            {SDL_SCANCODE_W, InputAction::UP_RELEASED},
            {SDL_SCANCODE_S, InputAction::DOWN_RELEASED},
            {SDL_SCANCODE_A, InputAction::LEFT_RELEASED},
            {SDL_SCANCODE_D, InputAction::RIGHT_RELEASED},
            {SDL_SCANCODE_E, InputAction::ACTION_RELEASED},
            {SDL_SCANCODE_SPACE, InputAction::JUMP_RELEASED}
    };

    std::unordered_map<SDL_Scancode, InputAction> keyMappingPressedPlayer2 = {
        {SDL_SCANCODE_UP, InputAction::UP_PRESSED},
        {SDL_SCANCODE_DOWN, InputAction::DOWN_PRESSED},
        {SDL_SCANCODE_LEFT, InputAction::LEFT_PRESSED},
        {SDL_SCANCODE_RIGHT, InputAction::RIGHT_PRESSED},
        {SDL_SCANCODE_RCTRL, InputAction::ACTION_PRESSED},
        {SDL_SCANCODE_RSHIFT, InputAction::JUMP_PRESSED}
    };

    std::unordered_map<SDL_Scancode, InputAction> keyMappingReleasedPlayer2 = {
        {SDL_SCANCODE_UP, InputAction::UP_RELEASED},
        {SDL_SCANCODE_DOWN, InputAction::DOWN_RELEASED},
        {SDL_SCANCODE_LEFT, InputAction::LEFT_RELEASED},
        {SDL_SCANCODE_RIGHT, InputAction::RIGHT_RELEASED},
        {SDL_SCANCODE_RCTRL, InputAction::ACTION_RELEASED},
        {SDL_SCANCODE_RSHIFT, InputAction::JUMP_RELEASED}
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
