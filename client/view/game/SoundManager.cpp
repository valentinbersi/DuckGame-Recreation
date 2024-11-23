#include "SoundManager.h"

#define MUSIC_PATH "assets/sounds/ost.ogg"
#define DEFAULT_VOLUME 10

SoundManager::SoundManager() {
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
