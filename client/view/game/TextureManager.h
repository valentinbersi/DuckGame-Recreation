#pragma once
#include <string>
#include <unordered_map>

#include <SDL2pp/SDL2pp.hh>

class TextureManager {

public:
    static void setRenderer(SDL2pp::Renderer& renderer);

    // Obtains a texture from the path... if it doesn't exist, it creates it inside the unordered
    // map called 'textures'.
    static SDL2pp::Texture& getTexture(const std::string& path);

private:
    static SDL2pp::Renderer* renderer;
    static std::unordered_map<std::string, SDL2pp::Texture> textures;
};
