#include "EnviromentRenderer.h"

EnviromentRenderer::EnviromentRenderer(SDL2pp::Renderer& renderer)
    : renderer(renderer){}

void EnviromentRenderer::drawEnviroment(SDL2pp::Rect& position, const char* path) {
    SDL_Texture* texture = TextureManager::getTexture(path, renderer).Get();
    if (texture == nullptr) {
        throw std::runtime_error("Texture is null in drawCube.");
    }
    SDL_RenderCopy(renderer.Get(), texture, nullptr, &position);
}
