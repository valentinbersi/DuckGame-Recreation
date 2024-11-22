#include "TextureManager.h"

SDL2pp::Renderer* TextureManager::renderer = nullptr;
std::unordered_map<std::string, SDL2pp::Texture> TextureManager::textures;

void TextureManager::setRenderer(SDL2pp::Renderer& newRenderer) {
    TextureManager::renderer = &newRenderer;
}

SDL2pp::Texture& TextureManager::getTexture(const std::string& path) {
    auto it = textures.find(path);
    if (it == textures.end())
        textures.emplace(path, SDL2pp::Texture(*renderer, path));
    return textures.at(path);
}
