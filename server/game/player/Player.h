#pragma once

#include "CollisionObject2D.h"
#include "Input.h"

class Player: public CollisionObject2D {
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

    void start() override;
    void update(float delta) override;
    void updateInternal(float delta) override;
    ~Player() override;
};
