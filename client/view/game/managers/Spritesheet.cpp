#include "Spritesheet.h"

#include <string>

#include "SpriteManager.h"

#define N_COL 5
#define N_ROW 2

#define WIDTH_HEIGHT_FEATHERS 16
#define WIDTH_HEIGHT_SPRITE 32

#define CHESTPLATE_PATH "assets/player/chestplate.png"
#define HELMET_PATH "assets/player/helmets.png"
#define WIN_PATH "assets/player/winner.png"

#define N_COL_F 5  // Feathers
#define N_ROW_F 8  // PERO NO LE DARÉ USO A TODAS

Spritesheet::Spritesheet(const char* path1, const char* path2, SDL2pp::Renderer& renderer):
        renderer(renderer), pathPlayer(path1), pathFeather(path2) {}

void Spritesheet::selectSprite(int x, int y, bool feathers) {
    if (feathers) {
        m_clip.w = WIDTH_HEIGHT_FEATHERS;
        m_clip.h = WIDTH_HEIGHT_FEATHERS;
    } else {
        m_clip.w = WIDTH_HEIGHT_SPRITE;
        m_clip.h = WIDTH_HEIGHT_SPRITE;
    }
    m_clip.x = x * m_clip.w;
    m_clip.y = y * m_clip.h;
}

void Spritesheet::damageEffects(double& m_x, double& m_y) {
    m_x += rand() % 5 - 2;
    m_y += rand() % 5 - 2;

    SDL_SetTextureColorMod(TextureManager::getTexture(pathPlayer, renderer).Get(), 255, 0, 0);
    SDL_SetTextureColorMod(TextureManager::getTexture(pathFeather, renderer).Get(), 255, 0, 0);
}

void Spritesheet::resetDamageEffects() {
    SDL_SetTextureColorMod(TextureManager::getTexture(pathPlayer, renderer).Get(), 255, 255, 255);
    SDL_SetTextureColorMod(TextureManager::getTexture(pathFeather, renderer).Get(), 255, 255, 255);
}

void Spritesheet::drawSelectedSprite(SDL2pp::Rect& position, bool flip, bool feathers) {
    SDL_RendererFlip flipType = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    SDL_Texture* texture = feathers ? TextureManager::getTexture(pathFeather, renderer).Get() :
                                      TextureManager::getTexture(pathPlayer, renderer).Get();

    if (texture == nullptr) throw std::runtime_error("Texture is null in drawSelectedSprite.");

    if (feathers) SDL_RenderCopyEx(renderer.Get(), texture, &m_clip, &position, angle, nullptr, flipType);
    else SDL_RenderCopyEx(renderer.Get(), texture, &m_clip, &position, 0.0, nullptr, flipType);
}

void Spritesheet::drawChestplate(SDL2pp::Rect& playerPosition, bool flip) {
    SDL_RendererFlip flipType = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer.Get(), TextureManager::getTexture(CHESTPLATE_PATH, renderer).Get(),
                     &m_clip, &playerPosition, 0.0, nullptr, flipType);
}

void Spritesheet::drawHelmet(SDL2pp::Rect& playerPosition, bool flip) {
    SDL_RendererFlip flipType = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer.Get(), TextureManager::getTexture(HELMET_PATH, renderer).Get(),
                     &m_clip, &playerPosition, angle, nullptr, flipType);
}

void Spritesheet::drawWeapon(SDL2pp::Rect& playerPosition, bool flip, std::string path) {
    SDL_RendererFlip flipType = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer.Get(), TextureManager::getTexture(path, renderer).Get(), &m_clip,
                     &playerPosition, angle, nullptr, flipType);
}

void Spritesheet::drawEffects(SDL2pp::Rect& playerPosition, bool flip, std::string path) {
    SDL_RendererFlip flipType = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer.Get(), TextureManager::getTexture(path, renderer).Get(), &m_clip,
                     &playerPosition, angle, nullptr, flipType);
}

void Spritesheet::drawWin(SDL2pp::Rect& playerPosition, bool flip) {
    SDL_RendererFlip flipType = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer.Get(), TextureManager::getTexture(WIN_PATH, renderer).Get(), &m_clip,
                     &playerPosition, 0.0, nullptr, flipType);
}

int Spritesheet::getClipWidth() const { return m_clip.w; }

int Spritesheet::getClipHeight() const { return m_clip.h; }

SDL_Rect& Spritesheet::getClip() { return m_clip; }

void Spritesheet::setAngle(float newAngle) { angle = newAngle; }
