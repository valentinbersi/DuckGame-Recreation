#include "Player.h"

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "Area.h"
#include "Bullet.h"
#include "DuckData.h"
#include "GameTimer.h"
#include "Item.h"
#include "ItemFactory.h"
#include "ItemID.h"
#include "Layer.h"
#include "WeaponFactory.h"
#include "GameController.h"

/**
 * Macro for easier event handling
 * @param Function The function to call
 * @param ... The type of the arguments to pass to the function
 */
#define eventHandler(Function, ...) \
    gameObject::EventHandler<Player __VA_ARGS__>::create(getReference<Player>(), Function)

#define DEFAULT_LIFE 30
#define DEFAULT_FLAGS 0
#define JUMP_TIME 0.2f
#define ACCELERATION 100
#define AIR_ACCELERATION 40
#define PLAYER_DIMENSIONS 2.0f, 2.875f
#define MOVE_RIGHT "Move Right"
#define MOVE_LEFT "Move Left"
#define CROUCH "Crouch"
#define JUMP "Jump"
#define INTERACT "Interact"
#define SHOOT "Shoot"
#define LOOK_UP "Look Up"
#define JUMP_TIMER "JumpTimer"
#define ITEM_DETECTOR "ItemDetector"

Player::Player(const DuckData::Id id):
        PhysicsObject({30, 0}, Layer::Player, Layer::Wall, PLAYER_DIMENSIONS, Gravity::Enabled,
                      Vector2::ZERO, CollisionType::Slide),
        id(id),
        _movementDirection(DuckData::Direction::Center),
        _viewDirection(DuckData::Direction::Right),
        _lastViewDirection(DuckData::Direction::Right),
        flags(DEFAULT_FLAGS),
        acceleration(ACCELERATION),
        airAcceleration(AIR_ACCELERATION),
        weapon(nullptr),
        isJumping(false),
        interactWithItem(false),
        actionateWeapon(false),
        canKeepJumping(true),
        jumpTimer(new GameTimer(JUMP_TIME)) {
    input.addAction(MOVE_RIGHT);
    input.addAction(MOVE_LEFT);
    input.addAction(CROUCH);
    input.addAction(JUMP);
    input.addAction(INTERACT);
    input.addAction(SHOOT);
    input.addAction(LOOK_UP);

    jumpTimer->connect(GameTimer::Events::Timeout, eventHandler(&Player::onJumpTimerTimeout));
    addChild(JUMP_TIMER, jumpTimer);

    connect(Events::Collision, eventHandler(&Player::onCollision, , CollisionObject*));

    const auto itemDetector = new Area(Vector2::ZERO, 0, Layer::Item, PLAYER_DIMENSIONS);
    itemDetector->connect(Events::Collision,
                          eventHandler(&Player::onItemCollision, , CollisionObject*));
    addChild(ITEM_DETECTOR, itemDetector);
}

#define WEAPON "Weapon"

void Player::onItemCollision(CollisionObject* item) {
    if (input.isActionJustPressed(INTERACT) and not weapon) {
        const auto itemPtr = static_cast<Item*>(item);  // Static cast is safe
        switch (const ItemID id = itemPtr->id()) {
            case ItemID::Helmet:
                flags |= flags.test(DuckData::Flag::Index::Helmet) ? flags : DuckData::Flag::Helmet;
                return;
            case ItemID::Armor:
                flags |= flags.test(DuckData::Flag::Index::Armor) ? flags : DuckData::Flag::Armor;
                return;
            default:
                weapon = WeaponFactory::createWeapon(id).release();
                weapon->connect(EquippableWeapon::Events::Fired,
                                eventHandler(&Player::onWeaponFired, , const Vector2&));
                addChild(WEAPON, weapon);
                item->parent()->removeChild(item);
        }
    }
}

void Player::onCollision(const CollisionObject* object) {
    if (object->layers().test(Layer::Index::DeathZone))
        return (void)setPosition({30, 0});

    if (object->layers().test(Layer::Index::Bullet))
        return kill();
}

void Player::onWeaponFired(const Vector2& recoil) {
    _velocity.setX(0);
    _velocity += recoil;
    flags.set(DuckData::Flag::Index::IsShooting);
}

void Player::onWeaponNoMoreBullets() { flags.set(DuckData::Flag::Index::NoMoreBullets); }

void Player::removeWeapon(){
    removeChild(WEAPON);
    weapon = nullptr;
}

void Player::onJumpTimerTimeout() { canKeepJumping = false; }

void Player::resetState() {
    isJumping = false;
    _movementDirection = DuckData::Direction::Center;
    _viewDirection = DuckData::Direction::Center;
    flags &= DuckData::Flag::IsDead | DuckData::Flag::Armor | DuckData::Flag::Helmet;
}

void Player::manageCrouch() {
    flags.set(DuckData::Flag::Index::PlayingDead);

    if (input.isActionPressed(MOVE_LEFT))
        _viewDirection.pushLeft();

    if (input.isActionPressed(MOVE_RIGHT))
        _viewDirection.pushRight();
}

void Player::manageInput() {
    if (flags.test(DuckData::Flag::Index::IsDead))
        return;

    if (input.isActionPressed(CROUCH)) {
        manageCrouch();
    } else {
        
        if (input.isActionPressed(JUMP) and _onGround)
            isJumping = true;

        if (input.isActionJustPressed(JUMP) and not _onGround)
            flags.set(DuckData::Flag::Index::Flapping);

        if (input.isActionPressed(MOVE_RIGHT)) {
            flags.set(DuckData::Flag::Index::IsMoving);
            _movementDirection.pushRight();
        }

        if (input.isActionPressed(MOVE_LEFT)) {
            flags.set(DuckData::Flag::Index::IsMoving);
            _movementDirection.pushLeft();
        }

        if (_movementDirection == DuckData::Direction::Center) {
            flags.reset(DuckData::Flag::Index::IsMoving);
            _viewDirection = _lastViewDirection;
        } else {
            _viewDirection = _movementDirection;
            _lastViewDirection = _viewDirection;
        }

        if (input.isActionPressed(LOOK_UP))
            flags.set(DuckData::Flag::Index::LookingUp);
    }

    if (input.isActionJustPressed(INTERACT))
        interactWithItem = true;

    if (input.isActionPressed(SHOOT))
        actionateWeapon = true;
    else
        actionateWeapon = false;
}

#define MIN_SPEED 0
#define MAX_SPEED 30

void Player::move(const float delta, const float movementAcceleration) {
    switch (_movementDirection) {
        case DuckData::Direction::Right:
            _velocity += Vector2::RIGHT * movementAcceleration * delta;
            break;
        case DuckData::Direction::Left:
            _velocity += Vector2::LEFT * movementAcceleration * delta;
            break;
        default:
            if (_velocity.x() > 0) {
                flags.set(DuckData::Flag::Index::IsMoving);
                _velocity += Vector2::LEFT * movementAcceleration * delta;
                if (_velocity.x() < MIN_SPEED)
                    _velocity.setX(MIN_SPEED);
            } else if (_velocity.x() < 0) {
                flags.set(DuckData::Flag::Index::IsMoving);
                _velocity += Vector2::RIGHT * movementAcceleration * delta;
                if (_velocity.x() > MIN_SPEED)
                    _velocity.setX(MIN_SPEED);
            }
    }

    if (_velocity.x() > MAX_SPEED)
        _velocity.setX(MAX_SPEED);
    else if (_velocity.x() < -MAX_SPEED)
        _velocity.setX(-MAX_SPEED);
}

void Player::performActionsInAir(const float delta) {
    move(delta, airAcceleration);
    if (not jumpTimer->started())
        jumpTimer->start();
}

void Player::performActionsInGround(const float delta) {
    move(delta, acceleration);
    jumpTimer->reset();
    canKeepJumping = true;
}

#define JUMP_SPEED 20

void Player::performActions(const float delta) {
    if (not _onGround)
        performActionsInAir(delta);
    else
        performActionsInGround(delta);

    if (isJumping and canKeepJumping)
        _velocity.setY(-JUMP_SPEED);
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

void Player::shoot() { input.pressAction(SHOOT); }

void Player::stopShoot() { input.releaseAction(SHOOT); }

void Player::lookUp() { input.pressAction(LOOK_UP); }

void Player::stopLookUp() { input.releaseAction(LOOK_UP); }

void Player::start() {}

void Player::update(const float delta) {
    resetState();
    if (flags.test(DuckData::Flag::Index::IsDead))
        return;
    manageInput();
    performActions(delta);


    // if (input.isActionPressed(JUMP) && _onGround) {
    //     _velocity += Vector2(0, -20);

    if (input.isActionJustPressed(JUMP) && !_onGround) {
        _velocity += Vector2(0, -3);
        flags |= DuckData::Flag::Flapping;

    } else if (input.isActionJustPressed(INTERACT) && weapon) {
        input.releaseAction(INTERACT);
        std::unique_ptr<Item> item = ItemFactory::createItem(weapon->getID());
        item->setPosition(globalPosition());
        getRoot<GameController>()->addToLevel("Item", std::move(item));
        removeWeapon();
    } 

    if (_velocity.x() < 0)
        _movementDirection = DuckData::Direction::Left;
    else if (_velocity.x() > 0)
        _movementDirection = DuckData::Direction::Right;

    if (weapon) {
        if (input.isActionPressed(SHOOT))
            weapon->actionate();
        else
            weapon->deactionate();
    }

    if (input.isActionPressed(LOOK_UP))
        flags |= DuckData::Flag::LookingUp;

    if (not _onGround)
        flags |= DuckData::Flag::InAir;
}

void Player::kill() {
    std::cout << "I DIED" << std::endl;

    if (flags.test(DuckData::Flag::Index::IsDead))
        return;

    flags.set(DuckData::Flag::Index::IsDead);
    removeFromLayer(Layer::Index::Player);
}

void Player::makeShoot() { flags |= DuckData::Flag::IsShooting; }

void Player::notMoreBullets() { flags |= DuckData::Flag::NoMoreBullets; }

DuckData::Direction Player::viewDirection() const { return _lastViewDirection; }

u32 Player::roundsWon() const { return wonRounds; }

void Player::winRound() { ++wonRounds; }

DuckData Player::status() {
    return {globalPosition(),
            id,
            _lastViewDirection,
            weapon ? weapon->getID() : ItemID(ItemID::NONE),
            flags,
            wonRounds};
}

void Player::clearInputs() { input.reset(); }

void Player::reset() {
    flags = 0;
    if (weapon) removeWeapon();
    setLayers(Layer::Player);
    clearInputs();
    _movementDirection = DuckData::Direction::Center;
    _viewDirection = DuckData::Direction::Right;
    _lastViewDirection = DuckData::Direction::Right;
    acceleration = ACCELERATION,
    airAcceleration = AIR_ACCELERATION;
    isJumping = false;
    interactWithItem= false;
    actionateWeapon = false;
    canKeepJumping = true;
}

bool Player::isDead() const {
    return flags.test(DuckData::Flag::Index::IsDead);
}

Player::~Player() = default;
