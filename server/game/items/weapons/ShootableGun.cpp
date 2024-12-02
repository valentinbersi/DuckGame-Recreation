#include "ShootableGun.h"

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

ShootableGun::~ShootableGun() = default;

ShootableGun::ShootableGun(const ItemID id, const u8 ammo, Vector2 recoil):
        EquippableWeapon(id, ammo, std::move(recoil)) {}
