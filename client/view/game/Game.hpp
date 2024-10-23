#pragma once

#include <exception>
#include <iostream>
#include <unordered_map>
#include <string>
#include "Player.h"

// #include <random>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/SDL2pp.hh>

class Game {

public:
    Game();
    ~Game();

    void init();

private:
    //void selectLevel();
    SDL2pp::Texture startBackground();
    Keybinds handleEvents();
    void getSnapshot();
    void update(Player& player1);
    //void render(Player player1);
    void showBackground(SDL2pp::Texture& backgroundTexture);

    bool running;
    Keybinds m_key;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;

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
