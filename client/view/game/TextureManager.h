#pragma once
#include <string>
#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>

class TextureManager {
public:
    // Constructor.
    explicit TextureManager(SDL2pp::Renderer& renderer);

    // Obtains a texture from the path... if it doesn't exist, it creates it inside the unordered
    // map called 'textures'.
    SDL2pp::Texture& getTexture(const std::string& path);

private:
    SDL2pp::Renderer& renderer;
    std::unordered_map<std::string, SDL2pp::Texture> textures;
};
