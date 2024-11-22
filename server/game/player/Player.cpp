#include "Player.h"

#include <memory>
#include <string>

#include "Debug.h"
#include "DuckData.h"
#include "GameTimer.h"
#include "GunID.h"

#define MOVE_RIGHT "Move Right"
#define MOVE_LEFT "Move Left"
#define CROUCH "Crouch"
#define JUMP "Jump"

#define DEFAULT_LIFE 10
#define DEFAULT_FLAGS 0
#define DEFAULT_SPEED 40

/**
 * Macro for easier event handling
 * @param Function The function to call
 * @param ... The type of the arguments to pass to the function
 */
#define eventHandler(Function, ...)                                                         \
    std::make_unique<gameObject::EventHandler<Player, __VA_ARGS__>>(getReference<Player>(), \
                                                                    Function)

Player::Player(const DuckID id):
        PhysicsObject(nullptr, {30, 10}, 1, 2, 2, 3, Gravity::Disabled),
        id(id),
        life(DEFAULT_LIFE),
        flags(DEFAULT_FLAGS),
        speed(DEFAULT_SPEED)
/* canKeepJumping(false)*/ {
    input.addAction(MOVE_RIGHT);
    input.addAction(MOVE_LEFT);
    input.addAction(CROUCH);
    input.addAction(JUMP);
    //     auto Timer = new GameTimer(1.0f);
    //     Timer->connect("Timeout", eventHandler([](Player* player) {
    //         player->canKeepJumping = false;
    //     }));
}

void Player::moveRight() { input.pressAction(MOVE_RIGHT); }

void Player::stopMoveRight() { input.releaseAction(MOVE_RIGHT); }

void Player::moveLeft() { input.pressAction(MOVE_LEFT); }

void Player::stopMoveLeft() { input.releaseAction(MOVE_LEFT); }

void Player::crouch() { input.pressAction(CROUCH); }

void Player::stopCrouch() { input.releaseAction(CROUCH); }

void Player::jump() { input.pressAction(JUMP); }

void Player::stopJump() { input.releaseAction(JUMP); }

void Player::start() {}

void Player::update([[maybe_unused]] const float delta) {
    Debug::cout().print("Position: " + std::to_string(globalPosition().x()) + ", " +
                        std::to_string(globalPosition().y()) + "\n");
    Debug::cout().flush();

    if (not input.isActionPressed(JUMP) and _velocity.y() < 0) {
        _velocity = _velocity.y(0);
    }
    _velocity = _velocity.x(0);
    flags = 0;

    if (input.isActionPressed(CROUCH)) {
        flags |= DuckData::CROUCHING;
    } else if (input.isActionPressed(MOVE_RIGHT)) {
        _velocity += Vector2(speed, 0);
        flags |= DuckData::MOVING_RIGHT;
    } else if (input.isActionPressed(MOVE_LEFT)) {
        _velocity += Vector2(-speed, 0);
        flags |= DuckData::MOVING_LEFT;
    } else if (input.isActionPressed(JUMP) && _onGround) {
        _velocity += Vector2(0, -10);
    }

    if (!_onGround) {}
    // flags |= DuckData::IN_AIR;
}

DuckData Player::status() { return {globalPosition(), id, life, GunID::Ak47, flags}; }

Player::~Player() = default;
