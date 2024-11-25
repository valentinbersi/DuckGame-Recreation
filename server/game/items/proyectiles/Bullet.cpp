#include "Bullet.h"

#include "Area.h"
#include "Layer.h"

#define BULLET_DIMENSIONS 0.375, 0.375

void Bullet::onCollision(CollisionObject* object) {
    switch (object->layers()) {
        case Layer::Player:
            // object->damage(damage);
            break;
        case Layer::Wall:
            return (void)parent()->removeChild(this);
        case Layer::Box:
            // object->damage(damage);
            break;
        default:
            break;
    }
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
    addChild("EntityDetectionArea", entityDetectionArea);
}
