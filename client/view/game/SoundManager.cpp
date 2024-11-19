#include "SoundManager.h"

#define MUSIC_PATH "../assets/sounds/DuckGameOST.mp3"
#define DEFAULT_VOLUME 40

SoundManager::SoundManager() {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) std::cerr << "Error: " << Mix_GetError() << std::endl;
    playMusic();
}

SoundManager::~SoundManager() {
    for (auto& music : musicMap) {
        Mix_FreeMusic(music.second);
    }
    musicMap.clear();

    for (auto& sound : soundMap) {
        Mix_FreeChunk(sound.second);
    }

    soundMap.clear();
    Mix_CloseAudio();
}

bool SoundManager::loadSound(GunID id) {
    const char* path = soundMapIDS[id];
    Mix_Chunk* sound = Mix_LoadWAV(path);
    if (sound == nullptr) {
        std::cerr << "Mix_LoadWAV Error: " << Mix_GetError() << std::endl;
        return false;
    }
    soundMap[id] = sound;
    return true;
}

void SoundManager::playMusic() {
    Mix_Music* music = Mix_LoadMUS(MUSIC_PATH);
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(DEFAULT_VOLUME);
}

void SoundManager::playSound(GunID id) {
    auto it = soundMap.find(id);
    if (it == soundMap.end()) loadSound(id);
    it = soundMap.find(id);

    Mix_PlayChannel(-1, it->second, 0);
}
