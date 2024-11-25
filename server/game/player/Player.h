#pragma once

#include <memory>

#include "CollisionObject.h"
#include "DuckData.h"
#include "EquippableWeapon.h"
#include "Input.h"
#include "PhysicsObject.h"

class Player final: public PhysicsObject {
    DuckData::Id id;
    i8 life;
    DuckData::Direction _direction;
    std::bitset<DuckData::FlagCount> flags;
    Input input;
    float speed;
    EquippableWeapon* weapon;
    bool isDead;

    /**
     * Event manager for the player colliding with an item
     */
    void onItemCollision(CollisionObject* item);

    /**
     * Event manager for the player firing a weapon
     * @param recoil The recoil of the weapon
     */
    void onWeaponFired(const Vector2& recoil);

    /**
     * Event manager for the player running out of bullets
     */
    void onWeaponNoMoreBullets();

    // bool canKeepJumping;

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
     * Damages the player
     * @param damage the amount of damage to deal
     */
    bool damage(u8 damage);

    /**
     * Makes the player shoot
     */
    void makeShoot();

    /**
     * Tell the player that it has no more bullets
     */
    void notMoreBullets();

    /**
     * Get the player's direction
     * @return the player's direction
     */
    DuckData::Direction direction() const;

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
