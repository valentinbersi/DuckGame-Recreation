#include "TextureManager.h"

TextureManager::TextureManager(SDL2pp::Renderer& renderer): renderer(renderer) {}

SDL2pp::Texture& TextureManager::getTexture(const std::string& path) {
    auto it = textures.find(path);
    if (it == textures.end())
        textures.emplace(path, SDL2pp::Texture(renderer, path));
    return textures.at(path);
}
