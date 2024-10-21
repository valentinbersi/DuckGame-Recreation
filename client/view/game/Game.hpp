#pragma once

#include <exception>
#include <iostream>
#include <unordered_map>
#include <string>

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
    void showBackground();

    bool running;
    SDL2pp::Window window;
    SDL2pp::Renderer renderer;

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
