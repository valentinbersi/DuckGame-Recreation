#pragma once

#include "CollisionObject.h"
#include "DuckData.h"
#include "Input.h"
#include "PhysicsObject.h"

class Player final: public PhysicsObject {
    DuckID id;
    u8 life;
    u16 flags;
    Input input;
    float speed;

protected:
    /**
     * Load the player's children
     */
    void loadChildren() override;

public:
    Player();
    ~Player() override;

    /**
     * Does nothing
     */
    void start() override;

    /**
     * Updates the player's position based on the input
     */
    void update(float delta) override;

    /**
     * Returns a GameStatus loaded with the player's data
     * @return a GameStatus loaded with the player's data
     */
    GameStatus status() override;

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
