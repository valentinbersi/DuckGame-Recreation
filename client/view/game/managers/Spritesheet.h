#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2pp/SDL2pp.hh>

class Spritesheet {
public:
    // Constructor.
    Spritesheet(std::string path1, std::string path2, SDL2pp::Renderer& renderer);

    // Destructor.
    ~Spritesheet() = default;

    // Selects the sprite to draw using coordinates of row and column. The boolean value sets the
    // width and height to 32 or 16. It ALSO sets the width and height of the clip.
    void selectSprite(int x, int y, bool feathers);

    void damageEffects(double& m_x, double& m_y);

    void resetDamageEffects() const;

    // Draws the selected sprite, using the textures that 'TextureManagers' has, depending if it's a
    // feather or not. Works with flipped sprites ;)
    void drawSelectedSprite(const SDL2pp::Rect& position, bool flip,
                            bool feathers /*, bool isRightFeather*/) const;

    // Draws the chestplate of the player... and same logic of the previous method.
    void drawChestplate(const SDL2pp::Rect& playerPosition, bool flip) const;

    // Blah blah blah, same logic of the previous method.
    void drawHelmet(const SDL2pp::Rect& playerPosition, bool flip, bool lookingUp, bool playingDead,
                    bool inAir) const;

    // Yes
    void drawWeapon(const SDL2pp::Rect& playerPosition, bool flip, const std::string& path) const;

    // ...
    void drawEffects(const SDL2pp::Rect& playerPosition, bool flip, const std::string& path);

    //
    void drawWin(const SDL2pp::Rect& playerPosition, bool flip, bool endGame) const;

    // Returns the width of the clip.
    int getClipWidth() const;

    // Returns the height of the clip.
    int getClipHeight() const;

    SDL_Rect& getClip();

    void setAngle(float newAngle);

private:
    SDL_Rect m_clip;
    SDL2pp::Renderer& renderer;
    std::string pathPlayer;
    std::string pathFeather;
    float angle;
};
