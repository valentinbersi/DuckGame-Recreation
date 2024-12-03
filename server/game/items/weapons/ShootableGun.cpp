#include "ShootableGun.h"

#include <utility>

#include "Box.h"
#include "DuckData.h"
#include "Layer.h"
#include "Player.h"
#include "RayCast.h"

RayCast* ShootableGun::generateBullet(const Vector2& direction, const float reach) {
    const auto bullet = new RayCast(
            parent<GameObject2D>()->globalPosition() + parent<Player>()->aimingDirection() * 3,
            direction, reach * 2, Layer::Wall | Layer::Box | Layer::Player);

    addChild("Bullet", bullet);
    return bullet;
}

void ShootableGun::onBulletCollision(CollisionObject* object) {
    if (object->layers().test(Layer::Index::Player))
        return static_cast<Player*>(object)->damage();

    if (object->layers().test(Layer::Index::Box))
        return static_cast<Box*>(object)->onCollision();
}

ShootableGun::~ShootableGun() = default;

ShootableGun::ShootableGun(const ItemID id, const u8 ammo, Vector2 recoil):
        EquippableWeapon(id, ammo, std::move(recoil)) {}

std::list<Segment2D> ShootableGun::status() const {
    std::list<Segment2D> bulletsStatus;
    for (const RayCast* bullet: bullets) {
        if (bullet != nullptr)
            bulletsStatus.push_back(bullet->getSegment());
    }
    return bulletsStatus;
}
