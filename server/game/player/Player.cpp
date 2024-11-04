#include "Player.h"

#include <memory>

#include "Capsule.h"
#include "DuckData.h"

#define MOVE_RIGHT "Move Right"
#define MOVE_LEFT "Move Left"

Player::Player():
        CollisionObject(nullptr, {0, 0}, 0, 0, 0,
                        std::make_unique<Capsule>(Vector2(0, 0), 0, 1, 3)),
        id(DuckID::White),
        life(3),
        flags(0),
        velocity(0, 0),
        speed(5) {

    input.addAction(MOVE_RIGHT);
    input.addAction(MOVE_LEFT);
}

void Player::moveRight() { input.pressAction(MOVE_RIGHT); }

void Player::stopMoveRight() { input.releaseAction(MOVE_RIGHT); }

void Player::moveLeft() { input.pressAction(MOVE_LEFT); }

void Player::stopMoveLeft() { input.releaseAction(MOVE_LEFT); }

void Player::start() {}

void Player::update(const float delta) {
    velocity = {0, 0};
    flags = 0;

    if (input.isActionPressed(MOVE_RIGHT)) {
        velocity += {speed, 0};
        flags |= DuckData::MOVING_RIGHT;

    } else if (input.isActionPressed(MOVE_LEFT)) {
        velocity += {-speed, 0};
        flags |= DuckData::MOVING_LEFT;
    }

    setPosition(position() + velocity * delta);
}

void Player::updateInternal(const float delta) { CollisionObject::updateInternal(delta); }

Player::~Player() = default;

GameStatus Player::status() {
    GameStatus status;
    status.gameObjects.push_back(
            std::make_unique<DuckData>(globalPosition(), globalRotation(), id, life,
                                       std::make_unique<EquippedGunData>(GunID::Ak47), flags));
    return status;
}
