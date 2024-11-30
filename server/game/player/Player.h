#pragma once

#include <memory>
#include <utility>

#include "CollisionObject.h"
#include "DuckData.h"
#include "EquippableWeapon.h"
#include "Input.h"
#include "PhysicsObject.h"

class GameTimer;

class Player final: public PhysicsObject {
    DuckData::Id id;
    DuckData::Direction _movementDirection;
    DuckData::Direction _viewDirection;
    DuckData::Direction _lastViewDirection;
    std::bitset<DuckData::FlagCount> flags;
    Input input;
    EquippableWeapon* weapon;
    bool isJumping;
    bool interactWithItem;
    bool actionateWeapon;
    bool canKeepJumping;
    GameTimer* jumpTimer;
    u32 wonRounds;

    /**
     * Event manager for the player colliding with an item
     */
    void onItemCollision(CollisionObject* item);

    /**
     * Event manager for the player colliding with an object
     */
    void onCollision(const CollisionObject* object);

    /**
     * Event manager for the player firing a weapon
     * @param recoil The recoil of the weapon
     */
    void onWeaponFired(const Vector2& recoil);

    /**
     * Event manager for the player running out of bullets
     */
    void onWeaponNoMoreBullets();

    /*
     * Event manager for the player's jump timer's timeouts
     */
    void onJumpTimerTimeout();

    /**
     * Reset the state of the player for a new frame
     */
    void resetState();

    /**
     * Manages the player's movement
     */
    void manageCrouch();

    /**
     * Manages the player's input
     */
    void manageInput();

    /**
     * Move the player
     */
    void move(float delta, float movementAcceleration);

    /**
     * Perform the actions of the player in the air
     */
    void performActionsInAir(float delta);

    /**
     * Perform the actions of the player in the ground
     * @param delta  The time since the last frame
     */
    void performActionsInGround(float delta);

    /**
     * Move the player, make him jump and interact with the environment
     */
    void performActions(float delta);

    /**
     * Removes the player Weapon
     */
    void removeWeapon();

public:
    Player() = delete;
    Player(const Player& other) = delete;
    Player(Player&& other) noexcept = delete;
    Player& operator=(const Player& other) = delete;
    Player& operator=(Player&& other) noexcept = delete;
    ~Player() override;

    /**
     * Creates a new player with the given id
     * @param id the id of the player
     */
    explicit Player(DuckData::Id id);

    /**
     * Does nothing
     */
    void start() override;

    /**
     * Updates the player's position based on the input
     */
    void update(float delta) override;

    /**
     * Kill the player
     */
    void kill();

    /**
     * Makes the player shoot
     */
    void makeShoot();

    /**
     * Tell the player that it has no more bullets
     */
    void notMoreBullets();

    /**
     * Get the player's view direction
     * @return the player's view direction
     */
    DuckData::Direction viewDirection() const;

    /**
     * Get the won rounds of the player
     * @return  the won rounds of the player
     */
    u32 roundsWon() const;

    /**
     * Makes the player win a round
     */
    void winRound();

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
     * Makes the player look up
     */
    void lookUp();

    /**
     * Makes the player stop looking up
     */
    void stopLookUp();

    /**
     * Clear player's inputs depending on force value
     */
    void clearInputs(Force force = Force::No);

    /**
     * Reset the player's state to the start of a round
     * it only mantains the amount of rounds won.
     */
    void reset();    

    /**
     *
     */
    bool isDead() const;
};
