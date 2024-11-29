#include "SoundManager.h"

#define MUSIC_PATH "assets/sounds/ost.ogg"
#define DEFAULT_VOLUME 10

#define CUACK "assets/sounds/cuack.mp3"
#define NO_MORE_BULLETS "assets/sounds/noMoreBullets.mp3"

SoundManager::SoundManager() : firstFrameDead(true) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 512) < 0)
        std::cerr << "Error: " << Mix_GetError() << std::endl;
    playMusic();
}

SoundManager::~SoundManager() {
    for (auto& sound: soundMap) {
        Mix_FreeChunk(sound.second);
    }

    soundMap.clear();
    Mix_CloseAudio();
}

void SoundManager::playMusic() {
    Mix_Music* music = Mix_LoadMUS(MUSIC_PATH);
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(DEFAULT_VOLUME);
}

void SoundManager::playSound(ItemID id) {
    auto it = soundMap.find(id);
    if (it == soundMap.end())
        loadSound(id);
    it = soundMap.find(id);

    Mix_VolumeChunk(it->second, 20);
    Mix_PlayChannel(-1, it->second, 0);
}

bool SoundManager::loadSound(ItemID id) {
    std::string path = soundMapIDS[id];
    Mix_Chunk* sound = Mix_LoadWAV(path.c_str());
    if (sound == nullptr) {
        std::cerr << "Mix_LoadWAV Error: " << Mix_GetError() << std::endl;
        return false;
    }
    soundMap[id] = sound;
    return true;
}

void SoundManager::playEffect(const std::string& path) {
    Mix_Chunk* effect = Mix_LoadWAV(path.c_str());
    if (effect == nullptr) {
        std::cerr << "Mix_LoadWAV Error: " << Mix_GetError() << std::endl;
        return;
    }

    Mix_VolumeChunk(effect, 20);
    Mix_PlayChannel(-1, effect, 0);
}

void SoundManager::checkSounds(DuckState& state) {
    if (state.isShooting)
        playSound(state.gunEquipped);
    if (state.isDead || firstFrameDead){
        firstFrameDead = false;
        playEffect(CUACK);
    }
    if (state.noMoreBullets)
        playEffect(NO_MORE_BULLETS);
    // faltan sonidos de fin de ronda, fin de partida y muerte
}
