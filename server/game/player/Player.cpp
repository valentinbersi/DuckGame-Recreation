#include "Player.h"

#include <memory>
#include <string>

#include "Area.h"
#include "Debug.h"
#include "DuckData.h"
#include "EquippableWeapon.h"
#include "GameTimer.h"
#include "Item.h"
#include "ItemID.h"
#include "Layer.h"
#include "WeaponFactory.h"

#define MOVE_RIGHT "Move Right"
#define MOVE_LEFT "Move Left"
#define CROUCH "Crouch"
#define JUMP "Jump"
#define INTERACT "Interact"

#define DEFAULT_LIFE 10
#define DEFAULT_FLAGS 0
#define DEFAULT_SPEED 40
#define PLAYER_DIMENSIONS 2.0f, 2.875f

/**
 * Macro for easier event handling
 * @param Function The function to call
 * @param ... The type of the arguments to pass to the function
 */
#define eventHandler(Function, ...) \
    gameObject::EventHandler<Player, __VA_ARGS__>::create(getReference<Player>(), Function)


Player::Player(const DuckID id):
        PhysicsObject(nullptr, {30, 0}, Layer::Player, Layer::Wall, PLAYER_DIMENSIONS,
                      Gravity::Enabled),
        id(id),
        life(DEFAULT_LIFE),
        flags(DEFAULT_FLAGS),
        speed(DEFAULT_SPEED),
        weapon(nullptr) {
    input.addAction(MOVE_RIGHT);
    input.addAction(MOVE_LEFT);
    input.addAction(CROUCH);
    input.addAction(JUMP);
    input.addAction(INTERACT);
    const auto itemDetector = new Area(nullptr, Vector2::ZERO, 0, Layer::Item, PLAYER_DIMENSIONS);
    itemDetector->connect("Collision", eventHandler(&Player::onItemCollision, CollisionObject*));
    addChild("ItemDetector", itemDetector);
}

void Player::onItemCollision(CollisionObject* item) {
    if (input.isActionPressed(INTERACT) and not weapon) {
        Item* itemPtr = dynamic_cast<Item*>(item);
        ItemID id = itemPtr->id();
        switch (id) {
            case ItemID::Helmet:
                flags |= (flags & DuckData::HELMET) ? flags : DuckData::HELMET;
                return;
            case ItemID::Armor:
                flags |= (flags & DuckData::ARMOR) ? flags : DuckData::ARMOR;
                return;
            default:

                return;
        }
        input.releaseAction(INTERACT);
    }
}

void Player::moveRight() { input.pressAction(MOVE_RIGHT); }

void Player::stopMoveRight() { input.releaseAction(MOVE_RIGHT); }

void Player::moveLeft() { input.pressAction(MOVE_LEFT); }

void Player::stopMoveLeft() { input.releaseAction(MOVE_LEFT); }

void Player::crouch() { input.pressAction(CROUCH); }

void Player::stopCrouch() { input.releaseAction(CROUCH); }

void Player::jump() { input.pressAction(JUMP); }

void Player::stopJump() { input.releaseAction(JUMP); }

void Player::interact() { input.pressAction(INTERACT); }

void Player::start() {}

void Player::update([[maybe_unused]] const float delta) {
    Debug::cout().print("Position: " + std::to_string(globalPosition().x()) + ", " +
                        std::to_string(globalPosition().y()) + "\n");
    Debug::cout().flush();

    if (not input.isActionPressed(JUMP) and _velocity.y() < 0) {
        _velocity = _velocity.y(0);
    }
    _velocity = _velocity.x(0);
    flags &= DuckData::ARMOR | DuckData::HELMET;

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
    } else if (input.isActionPressed(INTERACT)) {
        input.releaseAction(INTERACT);
        // ItemID id = weapon->getID();
        // ItemFactory::createItem(id);
        // weapon = nullptr;
    }

    if (!_onGround)
        flags |= DuckData::IN_AIR;
}

DuckData Player::status() { return {globalPosition(), id, life, ItemID::Ak47, flags}; }

Player::~Player() = default;
