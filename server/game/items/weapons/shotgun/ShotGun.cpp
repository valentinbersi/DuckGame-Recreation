#include "ShotGun.h"

#include <utility>

#include "Config.h"
#include "GameController.h"
#include "Layer.h"
#include "Math.h"
#include "Player.h"

Shotgun::Shotgun(const ItemID id, const u8 ammo, Vector2 recoil, const float minReach,
                 const float maxReach, const float dispersion, const u8 pellets):
        ShootableGun(id, ammo, std::move(recoil)),
        minReach(minReach),
        maxReach(maxReach),
        firing(false),
        fireNextFrame(false),
        hasToReload(false),
        randomDistanceGenerator(minReach, maxReach),
        randomDispersionGenerator(-dispersion, dispersion) {
    bullets.resize(pellets);
}

void Shotgun::update([[maybe_unused]] float delta) {
    using gameObject::EventHandler;
    if (bullets.front()) {
        for (RayCast*& pellet: bullets) {
            removeChild(pellet);
            pellet = nullptr;
        }
    }

    if (not fireNextFrame)
        return;

    if (not fire()) {
        fireNextFrame = false;
        return;
    }

    fireNextFrame = false;
    for (RayCast*& pellet: bullets) {
        pellet = generateBullet(
                parent<Player>()->aimingDirection().rotated(randomDispersionGenerator()),
                randomDistanceGenerator());
        pellet->connect(RayCast::Events::Collision,
                        EventHandler<ShootableGun, CollisionObject*>::create(
                                getReference<ShootableGun>(), &ShootableGun::onBulletCollision));
    }

    hasToReload = true;
}

void Shotgun::actionate() {
    if (firing)
        return;

    if (hasToReload) {
        hasToReload = false;
        firing = true;
        return;
    }

    firing = true;
    fireNextFrame = true;
}

void Shotgun::deactionate() {
    firing = false;
    fireNextFrame = false;
}

Shotgun::~Shotgun() = default;
