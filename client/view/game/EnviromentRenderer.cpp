#include "EnviromentRenderer.h"

EnviromentRenderer::EnviromentRenderer(SDL2pp::Renderer& renderer): renderer(renderer) {}

void EnviromentRenderer::drawEnviroment(SDL2pp::Rect& position, const char* path) {
    SDL_Texture* texture = TextureManager::getTexture(path, renderer).Get();
    if (texture == nullptr) {
        throw std::runtime_error("Texture is null in drawCube.");
    }
    SDL_RenderCopy(renderer.Get(), texture, nullptr, &position);
}

void EnviromentRenderer::drawBullets(const std::list<std::pair<Vector2, Vector2>>& bulletPositions) {
    for (const auto& position : bulletPositions) {
        SDL_SetRenderDrawColor(renderer.Get(), 255, 255, 255, 255); // Color blanco
        SDL_RenderDrawLine(renderer.Get(), position.first.x(), position.first.y(), position.second.x(), position.second.y());
    }
}
