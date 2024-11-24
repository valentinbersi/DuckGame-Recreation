#pragma once

#include <memory>

#include "CollisionObject.h"
#include "DuckData.h"
#include "EquippableWeapon.h"
#include "Input.h"
#include "PhysicsObject.h"

class Player final: public PhysicsObject {
private:
    DuckID id;
    u8 life;
    u16 flags;
    Input input;
    float speed;
    EquippableWeapon* weapon;

    /**
     *
     */
    void onItemCollision(CollisionObject* item);
    // bool canKeepJumping;

public:
    explicit Player(DuckID id);
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
    DuckData status();

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
     * Makes the player crouch
     */
    void crouch();

    /**
     * Stops the player from crouching
     */
    void stopCrouch();

    /**
     * Makes the player to jump
     */
    void jump();

    /**
     * Stops the player from jumping
     */
    void stopJump();

    /**
     * Makes the player interact with the environment
     */
    void interact();

    /**
     * Makes the player shoot
     */
    void shoot();

    /**
     * Makes the player stop shooting
     */
    void stopShoot();

    /**
     * Clear player's inputs that are just pressed, manains
     * input that are being pressed.
     */
    void clearInputs();
};
