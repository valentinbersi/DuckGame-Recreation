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
    // Constructor
    SoundManager();

    // Destructor
    ~SoundManager();

    /**
     * Plays the sound associated with the given ItemID
     * also it checks if the sound for the given ItemID is already loaded in the soundMap.
     * @param id: ItemID of the sound to be played
     */
    void playSound(ItemID id);

    /**
     * Loads the sound effect from the given path and plays it
     * @param path: path to the sound effect
     */
    void playEffect(const std::string& path);

    /**
     * Checks if the duck is dead and plays the sound effect
     * @param state: DuckState of the duck
     */
    void checkSounds(const DuckState& state);

private:
    // Plays the music in loop
    void playMusic();

    /**
     * Loads the sound associated with the given ItemID
     * @param id: ItemID of the sound to be loaded
     */
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
            {ItemID::PewPewLaser, Resource::get().resource("sounds/pew.mp3")}};
};
