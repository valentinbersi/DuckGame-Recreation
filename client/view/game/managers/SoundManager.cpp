#include "SoundManager.h"

#include "Resource.h"

#define MUSIC_PATH "sounds/ost.ogg"
#define DEFAULT_VOLUME 10

#define CUACK "sounds/cuack.mp3"
#define NO_MORE_BULLETS "sounds/noMoreBullets.mp3"

SoundManager::SoundManager(): firstFrameDead(true) {
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
    const std::string pathToMusic(Resource::get().resource(MUSIC_PATH));
    Mix_Music* music = Mix_LoadMUS(pathToMusic.c_str());
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

void SoundManager::checkSounds(const DuckState& state) {
    if (state.isShooting)
        playSound(state.gunEquipped);
    if (state.isDead || firstFrameDead) {
        firstFrameDead = false;
        playEffect(Resource::get().resource(CUACK));
    }
    if (state.noMoreBullets)
        playEffect(Resource::get().resource(NO_MORE_BULLETS));
    // faltan sonidos de fin de ronda, fin de partida y muerte
}
