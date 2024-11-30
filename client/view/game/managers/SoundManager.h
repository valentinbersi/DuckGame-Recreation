#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2pp/SDL2pp.hh>

#include "DuckData.h"
#include "DuckState.h"
#include "ItemID.h"

class SoundManager {

public:
    // Constructor.
    SoundManager();

    // Destructor.
    ~SoundManager();

    // Plays the sound associated with the given ItemID.
    // also it checks if the sound for the given ItemID is already loaded in the soundMap.
    void playSound(ItemID id);

    void playEffect(const std::string& path);

    void checkSounds(const DuckState& state);

private:
    // Plays the music in loop.
    void playMusic();

    // Loads the sound associated with the given ItemID.
    bool loadSound(ItemID id);

    bool firstFrameDead;

    std::unordered_map<ItemID, Mix_Chunk*> soundMap;
    std::unordered_map<ItemID, std::string> soundMapIDS{
            {ItemID::CowboyPistol, "assets/sounds/cowboyPistol.mp3"},
            {ItemID::Magnum, "assets/sounds/heavyShot.mp3"},
            {ItemID::DuelPistol, "assets/sounds/single-shot.mp3"},
            {ItemID::Ak47, "assets/sounds/shotgun.mp3"},
            {ItemID::Sniper, "assets/sounds/sniper.mp3"},
            {ItemID::Shotgun, "assets/sounds/shotgun.mp3"},
            {ItemID::LaserRifle, "assets/sounds/laser.mp3"},
            {ItemID::PewPewLaser, "assets/sounds/pew.mp3"}
            //{ItemID::Grenade, "assets/sounds/grenade.mp3"},
            //{ItemID::Banana, "assets/sounds/banana.mp3"},
    };
};
