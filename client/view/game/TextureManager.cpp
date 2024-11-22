#include "TextureManager.h"

std::unordered_map<std::string, SDL2pp::Texture> TextureManager::textures;

SDL2pp::Texture& TextureManager::getTexture(const std::string& path, SDL2pp::Renderer& renderer) {
    auto it = textures.find(path);
    if (it == textures.end())
        textures.emplace(path, SDL2pp::Texture(renderer, path));
    return textures.at(path);
}
