#include "Player.h"

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

#define MOVE_RIGHT "Move Right"
#define MOVE_LEFT "Move Left"
#define CROUCH "Crouch"
#define JUMP "Jump"
#define INTERACT "Interact"
#define SHOOT "Shoot"
#define LOOK_UP "Look Up"

#define DEFAULT_LIFE 30
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


Player::Player(const DuckData::Id id):
        PhysicsObject({30, 0}, Layer::Player, Layer::Wall, PLAYER_DIMENSIONS, Gravity::Enabled,
                      Vector2::ZERO, CollisionType::Slide),
        id(id),
        life(DEFAULT_LIFE),
        _direction(DuckData::Direction::Right),
        flags(DEFAULT_FLAGS),
        speed(DEFAULT_SPEED),
        weapon(nullptr),
        isDead(false) {
    input.addAction(MOVE_RIGHT);
    input.addAction(MOVE_LEFT);
    input.addAction(CROUCH);
    input.addAction(JUMP);
    input.addAction(INTERACT);
    input.addAction(SHOOT);
    input.addAction(LOOK_UP);

    connect(Events::Collision, eventHandler(&Player::onCollision, CollisionObject*));

    const auto itemDetector = new Area(Vector2::ZERO, 0, Layer::Item, PLAYER_DIMENSIONS);
    itemDetector->connect(Events::Collision,
                          eventHandler(&Player::onItemCollision, CollisionObject*));
    addChild("ItemDetector", itemDetector);
}

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
                addChild("Weapon", weapon);
                getRoot()->removeChild(item);
        }
    }
}

void Player::onCollision(CollisionObject* item) {
    if (item->layers().test(Layer::Index::DeathZone))
        return (void)setPosition({30, 0});

    if (item->layers().test(Layer::Index::Bullet))  // So static cast is safe
        return damage(static_cast<Bullet*>(item)->damage());
}

void Player::onWeaponFired(const Vector2& recoil) {
    _velocity.setX(0);
    _velocity += recoil;
    flags |= DuckData::Flag::IsShooting;
}

void Player::onWeaponNoMoreBullets() { flags |= DuckData::Flag::NoMoreBullets; }

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

void Player::update([[maybe_unused]] const float delta) {
    if (not input.isActionPressed(JUMP) and _velocity.y() < 0)
        _velocity = _velocity.y(0);

    _velocity = _velocity.x(0);
    flags &= DuckData::Flag::Armor | DuckData::Flag::Helmet;

    if (input.isActionPressed(CROUCH)) {
        flags |= DuckData::Flag::Crouching;

    } else if (input.isActionPressed(MOVE_RIGHT)) {
        _velocity += Vector2(speed, 0);
        flags |= DuckData::Flag::IsMoving;

    } else if (input.isActionPressed(MOVE_LEFT)) {
        _velocity += Vector2(-speed, 0);
        flags |= DuckData::Flag::IsMoving;

    } else if (input.isActionPressed(JUMP) && _onGround) {
        _velocity += Vector2(0, -20);

    } else if (input.isActionJustPressed(JUMP) && !_onGround) {
        _velocity += Vector2(0, -3);
        flags |= DuckData::Flag::Flapping;

    } else if (input.isActionJustPressed(INTERACT) && weapon) {
        std::unique_ptr<Item> item = ItemFactory::createItem(weapon->getID());
        item->setPosition(globalPosition());
        getRoot()->addChild("Weapon", std::move(item));
        removeChild("Weapon");
        weapon = nullptr;
    }

    if (_velocity.x() < 0)
        _direction = DuckData::Direction::Left;
    else if (_velocity.x() > 0)
        _direction = DuckData::Direction::Right;

    if (weapon) {
        if (input.isActionPressed(SHOOT))
            weapon->actionate();
        else
            weapon->deactionate();
    }

    if (input.isActionPressed(LOOK_UP))
        flags |= DuckData::Flag::LookingUp;
        //logica de apuntado para arriba, talvez direction es up??

    if (!_onGround)
        flags |= DuckData::Flag::InAir;
}

void Player::damage(const i8 damage) {
    if (isDead)
        return;

    life -= damage;
    if (life < 0)
        removeFromLayer(Layer::Player);
}

void Player::makeShoot() { flags |= DuckData::Flag::IsShooting; }

void Player::notMoreBullets() { flags |= DuckData::Flag::NoMoreBullets; }

DuckData::Direction Player::direction() const { return _direction; }

DuckData Player::status() {
    return {globalPosition(),
            id,
            life,
            _direction,
            weapon ? weapon->getID() : ItemID(ItemID::NONE),
            flags};
}

void Player::clearInputs() { input.reset(); }

Player::~Player() = default;
