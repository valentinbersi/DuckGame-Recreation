#include "Bullet.h"

#include <utility>

#include "Layer.h"
#include "Player.h"

#define BULLET_DIMENSIONS 0.375, 0.375
#define BULLET_SPEED 400

/**
 * Macro for easier event handling
 * @param Function The function to call
 * @param ... The type of the arguments to pass to the function
 */
#define eventHandler(Function, ...) \
    gameObject::EventHandler<Bullet, __VA_ARGS__>::create(getReference<Bullet>(), Function)

void Bullet::onCollision(CollisionObject* object) const {
    if (object->layers().test(Layer::Index::Player))
        static_cast<Player*>(object)->kill();
}

Bullet::Bullet(Vector2 direction, const u8 tiles):
        PhysicsObject(Vector2::ZERO, Layer::None, Layer::Player | Layer::Wall | Layer::Box,
                      BULLET_DIMENSIONS, Gravity::Disabled, std::move(direction * BULLET_SPEED),
                      CollisionType::Stop),
        tiles(tiles) {
    connect(Events::Collision, eventHandler(&Bullet::onCollision, CollisionObject*));
}

Bullet::~Bullet() = default;
