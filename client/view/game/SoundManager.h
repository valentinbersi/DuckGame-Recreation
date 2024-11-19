#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include "DuckData.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/SDL2pp.hh>

class SoundManager {

public:
    // Constructor.
    SoundManager();

    // Destructor.
    ~SoundManager();

    //
    void playSound(GunID id);

private:
    //
    void playMusic();

    //
    bool loadSound(GunID id);
    std::unordered_map<GunID, Mix_Chunk*> soundMap;
    std::unordered_map<GunID, std::string> soundMapIDS {
        {GunID::CowboyPistol, "../assets/sounds/cowboyPistol.mp3"}
    };
};
