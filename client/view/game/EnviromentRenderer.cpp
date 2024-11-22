#include "EnviromentRenderer.h"

EnviromentRenderer::EnviromentRenderer(SDL2pp::Renderer& renderer)
    : renderer(renderer){}

//crear posicion con la escala etc
// tipo
// int spriteWidth = spritesheet->getClipWidth();
// int spriteHeight = spritesheet->getClipHeight();
// return SDL2pp::Rect(m_position_x, m_position_y, spriteWidth * scale, spriteHeight * scale);

void EnviromentRenderer::drawEnviroment(SDL2pp::Rect& position, const char* path) {
    SDL_Texture* texture = TextureManager::getTexture(path).Get();
    if (texture == nullptr) {
        throw std::runtime_error("Texture is null in drawCube.");
    }
    SDL_RenderCopy(renderer.Get(), texture, nullptr, &position);
}