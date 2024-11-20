#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/SDL2pp.hh>

#include "DuckData.h"
#include "ItemID.h"

class SoundManager {

public:
    // Constructor.
    SoundManager();

    // Destructor.
    ~SoundManager();

    //
    void playSound(ItemID id);

private:
    //
    void playMusic();

    //
    bool loadSound(ItemID id);
    std::unordered_map<ItemID, Mix_Chunk*> soundMap;
    std::unordered_map<ItemID, std::string> soundMapIDS{
            {ItemID::CowboyPistol, "../assets/sounds/cowboyPistol.mp3"}};
};
