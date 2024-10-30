#include "Spritesheet.h"

Spritesheet::Spritesheet(const char* path1, const char* path2, SDL2pp::Renderer& renderer,
                         SDL2pp::Texture& m_texture_image, SDL2pp::Texture& m_texture_feathers):
        m_texture_image(m_texture_image),
        m_texture_feathers(m_texture_feathers),
        renderer(renderer),
        path1(path1),
        path2(path2) {

    m_spritesheet_image = IMG_Load(path1);
    m_spritesheet_feathers = IMG_Load(path2);
    if (!m_spritesheet_image || !m_spritesheet_feathers) {
        throw std::runtime_error("Failed to load spritesheet/s image");
    }
}

void Spritesheet::selectSprite(int x, int y, bool feathers) {
    if (feathers) {
        m_clip.w = m_spritesheet_feathers->w / N_COL_F;
        m_clip.h = m_spritesheet_feathers->h / N_ROW_F;
    } else {
        m_clip.w = m_spritesheet_image->w / N_COL;
        m_clip.h = m_spritesheet_image->h / N_ROW;
    }
    m_clip.x = x * m_clip.w;
    m_clip.y = y * m_clip.h;
}

void Spritesheet::drawSelectedSprite(SDL2pp::Rect& position, bool flip, bool feathers,
                                     bool isRightFeather) {
    SDL2pp::Texture m_texture_image(renderer, path1);
    SDL2pp::Texture m_texture_feathers(renderer, path2);

    SDL_RendererFlip flipType = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    if (feathers) {
        if (isRightFeather) {
            // Adjust position for the right feather
            position.x += m_clip.w;  // Example adjustment, change as needed
        } else {
            // Adjust position for the left feather
            position.x -= m_clip.w;  // Example adjustment, change as needed
        }
        SDL_RenderCopyEx(renderer.Get(), m_texture_feathers.Get(), &m_clip, &position, 0.0, nullptr,
                         flipType);
    } else {
        SDL_RenderCopyEx(renderer.Get(), m_texture_image.Get(), &m_clip, &position, 0.0, nullptr,
                         flipType);
    }
}

int Spritesheet::getClipWidth() const { return m_clip.w; }

int Spritesheet::getClipHeight() const { return m_clip.h; }
