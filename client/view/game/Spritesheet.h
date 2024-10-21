#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

class Spritesheet {

public:
    Spritesheet(const char* path, int row, int column, SDL2pp::Renderer& renderer);
    ~Spritesheet();

    void select_sprite(int x, int y);
    void draw_selected_sprite(SDL2pp::Renderer& renderer, SDL2pp::Rect& position, bool flip);
    int getClipWidth() const;
    int getClipHeight() const;

private:
    SDL_Rect m_clip;
    SDL_Surface* m_spritesheet_image;
    SDL2pp::Texture m_texture;
};
