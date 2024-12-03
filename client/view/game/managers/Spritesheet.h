#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>

class Spritesheet {
public:
    // Constructor
    Spritesheet(std::string path1, std::string path2, SDL2pp::Renderer& renderer);

    // Destructor
    ~Spritesheet() = default;

    /**
     * Selects the sprite to draw using coordinates of row and column. The boolean value sets the
     * width and height to 32 or 16. It ALSO sets the width and height of the clip
     * @param x: column
     * @param y: row
     * @param feathers: boolean value if it's a feather or not
     */
    void selectSprite(int x, int y, bool feathers);

    /**
     * Applies a effect to the player when it gets hit. It also changes the color of the
     * texture to red.
     * @param m_x: x coordinate
     * @param m_y: y coordinate
     */
    void damageEffects(double& m_x, double& m_y) const;

    /**
     * Resets the damage effects applied to the player
     */
    void resetDamageEffects() const;

    /**
     * Draws the selected sprite, using the textures that 'TextureManagers' has, depending if it's a
     * feather or not. Works with flipped sprites ;)
     * @param position: position of the sprite
     * @param flip: boolean value if it's flipped (looking left) or not
     * @param feathers: boolean value if it's a feather or not
     */
    void drawSelectedSprite(const SDL2pp::Rect& position, bool flip,
                            bool feathers) const;

    /**
     * Draws the chestplate of the player... and same logic of the previous method
     * @param playerPosition: position of the player
     * @param flip: boolean value if it's flipped (looking left) or not
     */
    void drawChestplate(const SDL2pp::Rect& playerPosition, bool flip) const;

    // Blah blah blah, same logic of the previous method.
    void drawHelmet(const SDL2pp::Rect& playerPosition, bool flip, bool lookingUp, bool playingDead,
                    bool inAir) const;

    // Yes
    void drawWeapon(const SDL2pp::Rect& playerPosition, bool flip, const std::string& path) const;

    // ...
    void drawEffects(const SDL2pp::Rect& playerPosition, bool flip, const std::string& path) const;

    // etc...
    void drawWin(const SDL2pp::Rect& playerPosition, bool flip, bool endGame) const;

    // Returns the width of the clip
    int getClipWidth() const;

    // Returns the height of the clip
    int getClipHeight() const;

    // Returns the clip
    SDL_Rect& getClip();

    // Updates the angle of rotation of the sprite
    void setAngle(float newAngle);

private:
    SDL_Rect m_clip;
    SDL2pp::Renderer& renderer;
    std::string pathPlayer;
    std::string pathFeather;
    float angle;
};
