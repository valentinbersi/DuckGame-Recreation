#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

#include "TextureManager.h"

class Spritesheet {
public:
    // Constructor.
    Spritesheet(const char* path1, const char* path2, SDL2pp::Renderer& renderer,
                TextureManager& textureManager);

    // Destructor.
    ~Spritesheet() = default;

    // Selects the sprite to draw using coordinates of row and column. The boolean value sets the
    // width and height to 32 or 16. It ALSO sets the width and height of the clip.
    void selectSprite(int x, int y, bool feathers);

    // Draws the selected sprite, using the textures that 'TextureManagers' has, depending if it's a
    // feather or not. Works with flipped sprites ;)
    void drawSelectedSprite(SDL2pp::Rect& position, bool flip,
                            bool feathers /*, bool isRightFeather*/);

    // Draws the chestplate of the player... and same logic of the previous method.
    void drawChestplate(SDL2pp::Rect& playerPosition, bool flip);

    // Blah blah blah, same logic of the previous method.
    void drawHelmet(SDL2pp::Rect& playerPosition, bool flip);

    // Yes
    void drawWeapon(SDL2pp::Rect& playerPosition, bool flip, std::string path);

    // ...
    void drawEffects(SDL2pp::Rect& playerPosition, bool flip, std::string path);

    // Returns the texture of the spritesheet, depending if it's a feather or not.
    SDL2pp::Texture& getTexture(bool feathers);

    // Returns the width of the clip.
    int getClipWidth() const;

    // Returns the height of the clip.
    int getClipHeight() const;

    SDL_Rect& getClip();

private:
    SDL_Rect m_clip;
    SDL2pp::Renderer& renderer;
    const char* pathPlayer;
    const char* pathFeather;
    TextureManager& textureManager;
};
