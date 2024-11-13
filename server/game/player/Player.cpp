#include "Player.h"

#include <memory>
#include <string>

#include "Capsule.h"
#include "Debug.h"
#include "DuckData.h"

#define MOVE_RIGHT "Move Right"
#define MOVE_LEFT "Move Left"
#define CROUCH "Crouch"

#define DEFAULT_LIFE 10
#define DEFAULT_FLAGS 0
#define DEFAULT_SPEED 100

Player::Player(const DuckID id):
        PhysicsObject(nullptr, {0, 0}, 0, 1, 2, std::make_unique<Capsule>(Vector2(0, 0), 0, 1, 3),
                      {0, 0}, Gravity::Enabled),
        id(id),
        life(DEFAULT_LIFE),
        flags(DEFAULT_FLAGS),
        speed(DEFAULT_SPEED) {
    input.addAction(MOVE_RIGHT);
    input.addAction(MOVE_LEFT);
    input.addAction(CROUCH);
}

void Player::moveRight() { input.pressAction(MOVE_RIGHT); }

void Player::stopMoveRight() { input.releaseAction(MOVE_RIGHT); }

void Player::moveLeft() { input.pressAction(MOVE_LEFT); }

void Player::stopMoveLeft() { input.releaseAction(MOVE_LEFT); }

void Player::crouch() { input.pressAction(CROUCH); }

void Player::stopCrouch() { input.releaseAction(CROUCH); }

void Player::start() {}

void Player::update(const float delta) {
    Debug::cout().print("Position: " + std::to_string(globalPosition().x()) + ", " +
                        std::to_string(globalPosition().y()) + "\n");
    Debug::cout().flush();

    setVelocity({0, 0});
    flags = 0;

    if (input.isActionPressed(CROUCH))
        flags |= DuckData::CROUCHING;
    else if (input.isActionPressed(MOVE_RIGHT)) {
        setVelocity((velocity() + Vector2(speed, 0)) * delta);
        flags |= DuckData::MOVING_RIGHT;
    } else if (input.isActionPressed(MOVE_LEFT)) {
        setVelocity((velocity() + Vector2(-speed, 0)) * delta);
        flags |= DuckData::MOVING_LEFT;
    }
}

Player::~Player() = default;

GameStatus Player::status() {
    GameStatus status;
    status.gameObjects.push_back(
            std::make_unique<DuckData>(globalPosition(), globalRotation(), id, life,
                                       std::make_unique<EquippedGunData>(GunID::Ak47), flags));
    return status;
}
