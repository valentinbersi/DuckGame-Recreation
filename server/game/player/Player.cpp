#include "Player.h"

#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include "Area.h"
#include "Bullet.h"
#include "Config.h"
#include "DuckData.h"
#include "EquippableItemFactory.h"
#include "GameController.h"
#include "GameTimer.h"
#include "Item.h"
#include "ItemFactory.h"
#include "ItemID.h"
#include "Layer.h"

/**
 * Macro for easier event handling
 * @param Function The function to call
 * @param ... The type of the arguments to pass to the function
 */
#define eventHandler(Function, ...) \
    gameObject::EventHandler<Player __VA_ARGS__>::create(getReference<Player>(), Function)

#define DEFAULT_LIFE 30
#define DEFAULT_FLAGS 0
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
#define EQUIPPED_ITEM "EquipedItem"

Player::Player(const DuckData::Id id):
        PhysicsObject({30, 0}, Layer::Player, Layer::Wall | Layer::Box, PLAYER_DIMENSIONS,
                      Gravity::Enabled, Vector2::ZERO, CollisionType::Slide),
        id(id),
        _movementDirection(DuckData::Direction::Center),
        _viewDirection(DuckData::Direction::Right),
        _lastViewDirection(DuckData::Direction::Right),
        flags(DEFAULT_FLAGS),
        item(nullptr),
        isJumping(false),
        interactWithItem(false),
        actionateWeapon(false),
        canKeepJumping(true),
        jumpTimer(new GameTimer(Config::Duck::jumpTime())),
        wonRounds(0),
        armorProtection(0),
        helmetProtection(0) {
    input.addAction(MOVE_RIGHT);
    input.addAction(MOVE_LEFT);
    input.addAction(CROUCH);
    input.addAction(JUMP);
    input.addAction(INTERACT);
    input.addAction(SHOOT);
    input.addAction(LOOK_UP);

    Config::Duck::defaultWeapon() == ItemID::NONE ?
            item = nullptr :
            item = EquippableItemFactory::createEquippableItem(Config::Duck::defaultWeapon())
                           .release();

    if (item) {
        item->connect(EquippableWeapon::Events::Fired,
                      eventHandler(&Player::onWeaponFired, , const Vector2&));
        item->connect(EquippableWeapon::Events::NoMoreBullets,
                      eventHandler(&Player::onWeaponNoMoreBullets));
        addChild(EQUIPPED_ITEM, item);
    }

    flags.set(DuckData::Flag::Index::Armor, Config::Duck::defaultArmor());
    flags.set(DuckData::Flag::Index::Helmet, Config::Duck::defaultHelmet());

    jumpTimer->connect(GameTimer::Events::Timeout, eventHandler(&Player::onJumpTimerTimeout));
    addChild(JUMP_TIMER, jumpTimer);

    connect(Events::Collision, eventHandler(&Player::onCollision, , CollisionObject*));

    const auto itemDetector = new Area(Vector2::ZERO, 0, Layer::Item, PLAYER_DIMENSIONS);
    itemDetector->connect(Events::Collision,
                          eventHandler(&Player::onItemCollision, , CollisionObject*));
    addChild(ITEM_DETECTOR, itemDetector);
}

void Player::onItemCollision(CollisionObject* itemDetected) {

    if (not input.isActionJustPressed(INTERACT) or item)
        return;

    const auto itemPtr = static_cast<Item*>(itemDetected);  // Static cast is safe
    const ItemID id = itemPtr->id();
    item = EquippableItemFactory::createEquippableItem(id).release();
    if (!(id == ItemID::Helmet || id == ItemID::Armor)) {
        item->connect(EquippableWeapon::Events::Fired,
                      eventHandler(&Player::onWeaponFired, , const Vector2&));
        item->connect(EquippableWeapon::Events::NoMoreBullets,
                      eventHandler(&Player::onWeaponNoMoreBullets));
    }
    addChild(EQUIPPED_ITEM, item);
    itemDetected->parent()->removeChild(itemDetected);
}

void Player::onCollision(const CollisionObject* object) {
    if (object->layers().test(Layer::Index::DeathZone))
        return (void)setGlobalPosition({30, 0});
}

void Player::onWeaponFired(const Vector2& recoil) {
    _velocity.setX(0);
    _velocity += recoil;
    flags.set(DuckData::Flag::Index::IsShooting);
}

void Player::onWeaponNoMoreBullets() { flags.set(DuckData::Flag::Index::NoMoreBullets); }

void Player::removeItem() {
    removeChild(EQUIPPED_ITEM);
    item = nullptr;
}

void Player::updateData() {
    if (_velocity.x() < 0)
        _movementDirection = DuckData::Direction::Left;
    else if (_velocity.x() > 0)
        _movementDirection = DuckData::Direction::Right;
}

void Player::onJumpTimerTimeout() { canKeepJumping = false; }

void Player::resetState() {
    interactWithItem = false;
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
        if (not input.isActionPressed(JUMP))
            canKeepJumping = false;

        if (input.isActionPressed(JUMP))
            isJumping = true;

        if (input.isActionJustPressed(JUMP) and not _onGround and _velocity.y() > 0)
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

    if (input.isActionPressed(LOOK_UP))
        flags |= DuckData::Flag::LookingUp;
}

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
                if (_velocity.x() < Config::Duck::minSpeed())
                    _velocity.setX(Config::Duck::minSpeed());
            } else if (_velocity.x() < 0) {
                flags.set(DuckData::Flag::Index::IsMoving);
                _velocity += Vector2::RIGHT * movementAcceleration * delta;
                if (_velocity.x() > Config::Duck::minSpeed())
                    _velocity.setX(Config::Duck::minSpeed());
            }
    }

    if (_velocity.x() > Config::Duck::maxSpeed())
        _velocity.setX(Config::Duck::maxSpeed());
    else if (_velocity.x() < -Config::Duck::maxSpeed())
        _velocity.setX(-Config::Duck::maxSpeed());
}

void Player::performActionsInAir(const float delta) {
    if (not jumpTimer->started())
        jumpTimer->start();

    if (flags.test(DuckData::Flag::Index::Flapping))
        _velocity.setY(0);

    move(delta, Config::Duck::airAcceleration());

    flags.set(DuckData::Flag::Index::InAir);
}

void Player::performActionsInGround(const float delta) {
    move(delta, Config::Duck::acceleration());
    jumpTimer->reset();
    canKeepJumping = true;
}

void Player::performActions(const float delta) {
    if (not _onGround)
        performActionsInAir(delta);
    else
        performActionsInGround(delta);

    if (isJumping and canKeepJumping)
        _velocity.setY(-Config::Duck::jumpSpeed());

    if (interactWithItem and item) {
        input.releaseAction(INTERACT);
        std::unique_ptr<Item> dropItem = ItemFactory::createItem(item->id());
        dropItem->setPosition(globalPosition());
        getRoot<GameController>()->addToLevel("Item", std::move(dropItem));
        removeItem();
    }

    if (item) {
        if (input.isActionPressed(SHOOT))
            item->actionate();
        else
            item->deactionate();
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
    updateData();
}

void Player::kill() {
    if (flags.test(DuckData::Flag::Index::IsDead))
        return;

    if (helmetProtection > 0) {
        --helmetProtection;
        if (helmetProtection == 0)
            flags.reset(DuckData::Flag::Index::Helmet);
        return;
    }

    if (armorProtection > 0) {
        --armorProtection;
        if (armorProtection == 0)
            flags.reset(DuckData::Flag::Index::Armor);
        return;
    }

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
            item ? item->id() : ItemID(ItemID::NONE),
            flags,
            wonRounds};
}

void Player::clearInputs(const Force force) { input.reset(force); }

void Player::reset() {
    flags.reset();
    if (item)
        removeItem();
    setLayers(Layer::Player);
    clearInputs(Force::Yes);
    _movementDirection = DuckData::Direction::Center;
    _viewDirection = DuckData::Direction::Right;
    _lastViewDirection = DuckData::Direction::Right;
    isJumping = false;
    interactWithItem = false;
    actionateWeapon = false;
    canKeepJumping = true;
}

bool Player::isDead() const { return flags.test(DuckData::Flag::Index::IsDead); }

bool Player::equipArmor(const u8 protection) {
    if (flags.test(DuckData::Flag::Index::Armor))
        return false;

    flags.set(DuckData::Flag::Index::Armor);
    armorProtection += protection;
    item = nullptr;
    return true;
}

bool Player::equipHelmet(const u8 protection) {
    if (flags.test(DuckData::Flag::Index::Helmet))
        return false;

    flags.set(DuckData::Flag::Index::Helmet);
    helmetProtection += protection;
    item = nullptr;
    return true;
}

Player::~Player() = default;
