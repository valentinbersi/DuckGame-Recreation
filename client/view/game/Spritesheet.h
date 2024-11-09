#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

// Spritesheet.h
class Spritesheet {
public:
    Spritesheet(const char* path1, const char* path2, SDL2pp::Renderer& renderer);
    ~Spritesheet();

    void selectSprite(int x, int y, bool feathers);
    void drawSelectedSprite(SDL2pp::Rect& position, bool flip, bool feathers/*, bool isRightFeather*/);
    int getClipWidth() const;
    int getClipHeight() const;

    SDL2pp::Texture* getTexture(bool feathers);

private:
    SDL_Rect m_clip;
    SDL_Surface* m_spritesheet_image;
    SDL_Surface* m_spritesheet_feathers;
    SDL2pp::Texture* m_texture_image;
    SDL2pp::Texture* m_texture_feathers;
    SDL2pp::Renderer& renderer;
    const char* path1;
    const char* path2;
};
