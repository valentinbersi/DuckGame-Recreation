#include "Player.h"

#define MOVE_RIGHT "Move Right"
#define MOVE_LEFT "Move Left"

Player::Player() {
    input.addAction(MOVE_RIGHT);
    input.addAction(MOVE_LEFT);
}

void Player::moveRight() { input.pressAction(MOVE_RIGHT); }

void Player::stopMoveRight() { input.releaseAction(MOVE_RIGHT); }

void Player::moveLeft() { input.pressAction(MOVE_LEFT); }

void Player::stopMoveLeft() { input.releaseAction(MOVE_LEFT); }
