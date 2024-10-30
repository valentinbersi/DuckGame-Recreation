#include "Player.h"

#include <memory>

#include "Capsule.h"

#define MOVE_RIGHT "Move Right"
#define MOVE_LEFT "Move Left"

Player::Player():
        CollisionObject2D(nullptr, {0, 0}, 0, 0, 0,
                          std::make_unique<Capsule>(Vector2(0, 0), 0, 1, 3)) {
    input.addAction(MOVE_RIGHT);
    input.addAction(MOVE_LEFT);
}

void Player::moveRight() { input.pressAction(MOVE_RIGHT); }

void Player::stopMoveRight() { input.releaseAction(MOVE_RIGHT); }

void Player::moveLeft() { input.pressAction(MOVE_LEFT); }

void Player::stopMoveLeft() { input.releaseAction(MOVE_LEFT); }

void Player::start() {}
