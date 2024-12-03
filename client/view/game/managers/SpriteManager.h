#pragma once

#include <memory>
#include <string>
#include <SDL2pp/SDL2pp.hh>

#include "DuckState.h"
#include "Spritesheet.h"
#include "WeaponSpriteManager.h"


class SpriteManager {
public:
    // Constructor
    SpriteManager(std::string path1, std::string path2,
                  SDL2pp::Renderer& renderer);

    // Destructor
    ~SpriteManager() = default;

    /**
     * Updates the sprite manager based on the current state of the duck
     * It then draws the appropriate sprite based on whether the duck is in the air, being damaged,
     * playing dead, or moving. This is done by calling the different draw methods
     * @param newState The new state of the duck
     */
    void update(const DuckState& newState);

    /** Draws the main sprite using the provided column and row indices
     * It then checks if the duck has a chestplate, helmet, or weapon equipped and draws them
     * accordingly. Finally, it draws the feathers based on whether the duck has a weapon equipped
     * @param col The column index of the sprite
     * @param row The row index of the sprite
     */
    void draw(int col, int row);

    /**
     * Adjusts the position and type of the winner screen
     * @param endGame draws a different type of 'win' if it is an endGame
     */
    void drawWin(bool endGame);

    /**
     * Updates the position of the duck
     * @param new_x The new x-coordinate of the duck
     * @param new_y The new y-coordinate of the duck
     */
    void updatePosition(float new_x, float new_y);

    /**
     * Sets the scale of the sprite
     * @param newScale The new scale of the sprite
     */
    void setScale(float newScale);

    /**
     * Returns the current state of the duck
     * @return The current state of the duck
     */
    DuckState& getState();

private:
    // Updates the internal flags of the SpriteManager based on the current state of the duck
    void setFlags();

    /**
     * Negates the flagToNegate if it is different from the flag
     * @param flag The flag to compare against
     * @param flagToNegate The flag to negate
     */
    void negateFlag(bool flag, bool& flagToNegate);

    /**
     * Draws the main sprite using the provided column and row indices
     * @param col The column index of the sprite
     * @param row The row index of the sprite
     */
    void drawMainSprite(int col, int row);

    /**
     * Draws the feathers based on the provided column and row indices and whether the duck has a
     * weapon equipped. Also it checks a lot of other flags
     * @param col The column index of the sprite
     * @param row The row index of the sprite
     */
    void drawFeathers(int col, int row);

    // Draws the flapping frames
    void drawFlapping();

    /**
     * Draws the chestplate based on the provided column and row indices
     * Also it checks other flags
     * @param col The column index of the sprite
     * @param row The row index of the sprite
     */
    void drawChestplate(int col, int row);

    // Draws the helmet. Also checks other flags
    void drawHelmet();

    /**
     * Returns the position of the sprite based on the provided flags
     * @param isFeather Whether the sprite is a feather
     * @param isChestPlate Whether the sprite is a chestplate
     * @param isHelmet Whether the sprite is a helmet
     * @return The position of the sprite to be drawn in an SDL2pp Rectangle
     */
    SDL2pp::Rect getPosition(bool isFeather, bool isChestPlate, bool isHelmet);

    /**
     * Returns the base position of the sprite based on the current position of the duck
     * Meaning... this is the position of the duck and only the duck sprite
     * @return The base position of the sprite to be drawn in an SDL2pp Rectangle
     */
    SDL2pp::Rect calculateBasePosition() const;

    /**
     * Adjusts the position of the sprite for the feathers
     * @param position The position of the sprite to be adjusted
     */
    void adjustForFeathers(SDL2pp::Rect& position) const;

    /**
     * Adjusts the position of the sprite for the helmet
     * @param position The position of the sprite to be adjusted
     */
    void adjustForHelmet(SDL2pp::Rect& position) const;

    /**
     * Adjusts the position of the sprite for the chestplate
     * @param position The position of the sprite to be adjusted
     */
    void adjustForChestplate(SDL2pp::Rect& position);


    std::string path1;
    std::string path2;
    float scale;
    bool isMoving;
    bool inAir;
    bool flapping;
    bool dead;
    std::unique_ptr<Spritesheet> spritesheet;
    std::unique_ptr<WeaponSpriteManager> weaponSpriteManager;
    DuckState state;
    int frame;
    int flappingFrame;
    double m_position_x;
    double m_position_y;
};
