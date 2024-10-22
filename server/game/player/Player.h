#pragma once

#include "Input.h"

class Player /*: public ¿Object2D? */ {
    Input input;

public:
    Player();

    /**
     * Move the player to the right until stopMoveRight() is called
     */
    void moveRight();

    /**
     * Stops the player from moving to the right, if moveRight() was not called before this method,
     * it does nothing
     */
    void stopMoveRight();

    /**
     * Move the player to the left until stopMoveLeft() is called.
     */
    void moveLeft();

    /**
     * Stops the player from moving to the left if moveLeft() was not called before this method, it
     * does nothing
     */
    void stopMoveLeft();
};
