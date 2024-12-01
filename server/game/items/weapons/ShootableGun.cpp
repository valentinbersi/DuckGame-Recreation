#include "ShootableGun.h"

#include "DuckData.h"
#include "Player.h"
#include "RayCast.h"

RayCast* ShootableGun::generateBullet(const Vector2& direction, const float reach) {
    const auto bullet =
            new RayCast(parent<GameObject2D>()->globalPosition() +
                                (parent<Player>()->viewDirection() == DuckData::Direction::Right ?
                                         Vector2::RIGHT * 2 :
                                         Vector2::LEFT * 2),
                        direction, reach * 2);

    addChild("Bullet", bullet);
    return bullet;
}

ShootableGun::~ShootableGun() = default;

ShootableGun::ShootableGun(const ItemID id, const u8 ammo, Vector2 recoil):
        EquippableWeapon(id, ammo, std::move(recoil)) {}
