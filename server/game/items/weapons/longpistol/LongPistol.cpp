#include "LongPistol.h"

#include <memory>
#include <utility>

#include "Bullet.h"
#include "Player.h"

#define BULLET_TILES 20
#define BULLET_SPEED 400
#define BULLET_DAMAGE 10

LongPistol::LongPistol(const ItemID id, const u8 ammo, Vector2 recoil, const float reach,
                       const float dispersion):
        EquippableWeapon(id, ammo, std::move(recoil)),
        reach(reach),
        firing(false),
        randomGenerator(-dispersion, dispersion) {}

void LongPistol::actionate() {
    if (firing)
        return;

    firing = true;
    fire();

    const Vector2 direction =
            (parent<Player>()->viewDirection() == DuckData::Direction::Right ? Vector2::RIGHT :
                                                                               Vector2::LEFT)
                    .rotated(randomGenerator());

    auto bullet = std::make_unique<Bullet>(direction * BULLET_SPEED, reach);
    bullet->setGlobalPosition(
            parent<Player>()->globalPosition() +
                    (parent<Player>()->viewDirection() == DuckData::Direction::Right ?
                             Vector2::RIGHT * 2 :
                             Vector2::LEFT * 2),
            Force::Yes);

    getRoot()->addChild("Bullet", std::move(bullet));
}

void LongPistol::deactionate() { firing = false; }

LongPistol::~LongPistol() = default;
