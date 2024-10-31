#pragma once

#include "CollisionObject.h"
#include "DuckData.h"
#include "Input.h"

class Player final: public CollisionObject {
    DuckID id;
    u8 life;
    u16 flags;
    Input input;
    Vector2 velocity;
    float speed;

public:
    Player();
    ~Player() override;

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

    /**
     * For now does nothing
     */
    void start() override;

    /**
     * Updates the player's position based on the input
     */
    void update(float delta) override;

    /**
     * Update the player's internal state
     */
    void updateInternal(float delta) override;

    /**
     * Returns a GameStatus loaded with the player's data
     * @return a GameStatus loaded with the player's data
     */
    GameStatus status() override;
};
