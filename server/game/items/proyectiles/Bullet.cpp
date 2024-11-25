#include "Bullet.h"

#include "Area.h"
#include "Layer.h"
#include "Player.h"

#define BULLET_DIMENSIONS 0.375, 0.375

/**
 * Macro for easier event handling
 * @param Function The function to call
 * @param ... The type of the arguments to pass to the function
 */
#define eventHandler(Function, ...) \
    gameObject::EventHandler<Bullet, __VA_ARGS__>::create(getReference<Bullet>(), Function)

void Bullet::onCollision(CollisionObject* object) const {
    bool impact = true;

    switch (object->layers()) {
        case Layer::Player:
            impact = static_cast<Player*>(object)->damage(damage);
            break;
        case Layer::Box:
            // object->damage(damage); // TODO: implement boxes
            break;
        default:;
    }

    if (impact)
        parent()->removeChild(this);
}

Bullet::Bullet(const u8 damage, Vector2 velocity, const u8 tiles):
        PhysicsObject(nullptr, Vector2::ZERO, Layer::None, Layer::None, BULLET_DIMENSIONS,
                      Gravity::Disabled),
        damage(damage),
        tiles(tiles) {
    _velocity = std::move(velocity);

    const auto entityDetectionArea =
            new Area(nullptr, Vector2::ZERO, Layer::None, Layer::Player | Layer::Wall | Layer::Box,
                     BULLET_DIMENSIONS);
    entityDetectionArea->connect(Area::Events::Collision,
                                 eventHandler(&Bullet::onCollision, CollisionObject*));
    addChild("EntityDetectionArea", entityDetectionArea);
}
