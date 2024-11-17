#pragma once
#include <SDL2pp/SDL2pp.hh>
#include <unordered_map>
#include <string>

class TextureManager {
public:
    TextureManager(SDL2pp::Renderer& renderer);
    SDL2pp::Texture& getTexture(const std::string& path);

private:
    SDL2pp::Renderer& renderer;
    std::unordered_map<std::string, SDL2pp::Texture> textures;

};
