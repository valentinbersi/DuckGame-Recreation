#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include <SDL2/SDL_mixer.h>

#include "DuckState.h"
#include "ItemID.h"
#include "Resource.h"

class SoundManager {

public:
    // Constructor.
    SoundManager();

    // Destructor.
    ~SoundManager();

    // Plays the sound associated with the given ItemID.
    // also it checks if the sound for the given ItemID is already loaded in the soundMap.
    void playSound(const ItemID id);

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
            {ItemID::CowboyPistol, Resource::get().resource("sounds/cowboyPistol.mp3")},
            {ItemID::Magnum, Resource::get().resource("sounds/heavyShot.mp3")},
            {ItemID::DuelPistol, Resource::get().resource("sounds/single-shot.mp3")},
            {ItemID::Ak47, Resource::get().resource("sounds/shotgun.mp3")},
            {ItemID::Sniper, Resource::get().resource("sounds/sniper.mp3")},
            {ItemID::Shotgun, Resource::get().resource("sounds/shotgun.mp3")},
            {ItemID::LaserRifle, Resource::get().resource("sounds/laser.mp3")},
            {ItemID::PewPewLaser, Resource::get().resource("sounds/pew.mp3")}
            //{ItemID::Grenade, "sounds/grenade.mp3"},
            //{ItemID::Banana, "sounds/banana.mp3"},
    };
};
