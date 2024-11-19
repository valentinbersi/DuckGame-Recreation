#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>
#include "TextureManager.h"

class Spritesheet {
public:
    Spritesheet(const char* path1, const char* path2, SDL2pp::Renderer& renderer, TextureManager& textureManager);
    ~Spritesheet();

    void selectSprite(int x, int y, bool feathers);
    void drawSelectedSprite(SDL2pp::Rect& position, bool flip, bool feathers/*, bool isRightFeather*/);
    void drawChestplate(SDL2pp::Rect& playerPosition, bool flip);
    void drawHelmet(SDL2pp::Rect& playerPosition, bool flip);
    void drawWeapon(SDL2pp::Rect& playerPosition, bool flip, std::string path);
    int getClipWidth() const;
    int getClipHeight() const;

    SDL2pp::Texture& getTexture(bool feathers);

private:
    SDL_Rect m_clip;
    SDL2pp::Renderer& renderer;
    const char* pathPlayer;
    const char* pathFeather;
    TextureManager& textureManager;
};
