#include "Spritesheet.h"

#define N_COL 5
#define N_ROW 2

#define WIDTH_HEIGHT_FEATHERS 16
#define WIDTH_HEIGHT_SPRITE 32

#define N_COL_F 5  // Feathers
#define N_ROW_F 8  // PERO NO LE DARÉ USO A TODAS

Spritesheet::Spritesheet(const char* path1, const char* path2, SDL2pp::Renderer& renderer, TextureManager& textureManager):
        renderer(renderer), pathPlayer(path1), pathFeather(path2), textureManager(textureManager) {}

Spritesheet::~Spritesheet() {
    //delete m_texture_image;
    //delete m_texture_feathers;
}

void Spritesheet::selectSprite(int x, int y, bool feathers) {
    if (feathers) {
        m_clip.w = WIDTH_HEIGHT_FEATHERS;
        m_clip.h = WIDTH_HEIGHT_FEATHERS;
        /*
        m_clip.w = m_spritesheet_feathers->w / N_COL_F;
        m_clip.h = m_spritesheet_feathers->h / N_ROW_F;*/
    } else {
        m_clip.w = WIDTH_HEIGHT_SPRITE;
        m_clip.h = WIDTH_HEIGHT_SPRITE;
        /*
        m_clip.w = m_spritesheet_image->w / N_COL;
        m_clip.h = m_spritesheet_image->h / N_ROW;*/
    }
    m_clip.x = x * m_clip.w;
    m_clip.y = y * m_clip.h;
}

void Spritesheet::drawSelectedSprite(SDL2pp::Rect& position, bool flip, bool feathers/*,
                                     bool isRightFeather*/) {
    SDL_RendererFlip flipType = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

    SDL_Texture* texture = feathers ? textureManager.getTexture(pathFeather).Get() : textureManager.getTexture(pathPlayer).Get();

    if (texture == nullptr) {
        throw std::runtime_error("Texture is null in drawSelectedSprite.");
    }

    SDL_RenderCopyEx(renderer.Get(), texture, &m_clip, &position, 0.0, nullptr, flipType);
}

SDL2pp::Texture& Spritesheet::getTexture(bool feathers) {
    if (feathers) return textureManager.getTexture(pathFeather);
    return textureManager.getTexture(pathPlayer);
}

int Spritesheet::getClipWidth() const { return m_clip.w; }

int Spritesheet::getClipHeight() const { return m_clip.h; }
