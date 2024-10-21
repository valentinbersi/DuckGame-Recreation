#include "Spritesheet.h"

Spritesheet::Spritesheet(const char* path, int row, int column, SDL2pp::Renderer& renderer)
    : m_texture(renderer, path) {
    m_spritesheet_image = IMG_Load(path);
    if (!m_spritesheet_image) {
        throw std::runtime_error("Failed to load spritesheet image");
    }

    m_clip.w = m_spritesheet_image->w / column;
    m_clip.h = m_spritesheet_image->h / row;
}

Spritesheet::~Spritesheet() {
}

void Spritesheet::select_sprite(int x, int y) {
    m_clip.x = x * m_clip.w;
    m_clip.y = y * m_clip.h;
}

void Spritesheet::draw_selected_sprite(SDL2pp::Renderer& renderer, SDL2pp::Rect& position, bool flip) {
    SDL_RendererFlip flipType = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer.Get(), m_texture.Get(), &m_clip, &position, 0.0, nullptr, flipType);
}

int Spritesheet::getClipWidth() const {
    return m_clip.w;
}

int Spritesheet::getClipHeight() const {
    return m_clip.h;
}
