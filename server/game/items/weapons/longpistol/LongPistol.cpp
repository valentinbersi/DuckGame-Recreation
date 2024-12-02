#include "LongPistol.h"

#include <utility>

#include "GameController.h"
#include "Layer.h"
#include "Player.h"
#include "RayCast.h"

#define BULLET_TILES 20
#define BULLET_DAMAGE 10

void LongPistol::onBulletCollision(CollisionObject* object) {
    if (object->layers().test(Layer::Index::Player))
        static_cast<Player*>(object)->damage();
}

LongPistol::LongPistol(const ItemID id, const u8 ammo, Vector2 recoil, const float reach,
                       const float dispersion):
        ShootableGun(id, ammo, std::move(recoil)),
        reach(reach),
        firing(false),
        fireNextFrame(false),
        randomGenerator(-dispersion, dispersion),
        bullet(nullptr) {}

void LongPistol::update([[maybe_unused]] float delta) {
    using gameObject::EventHandler;

    if (bullet) {
        removeChild(bullet);
        bullet = nullptr;
    }

    if (not fireNextFrame)
        return;

    if (not fire()) {
        fireNextFrame = false;
        return;
    }

    fireNextFrame = false;
    bullet = generateBullet(parent<Player>()->aimingDirection().rotated(randomGenerator()), reach);
    bullet->connect(RayCast::Events::Collision,
                    EventHandler<LongPistol, CollisionObject*>::create(
                            getReference<LongPistol>(), &LongPistol::onBulletCollision));
}

void LongPistol::actionate() {
    if (firing)
        return;

    firing = true;
    fireNextFrame = true;
}

void LongPistol::deactionate() {
    firing = false;
    fireNextFrame = false;
}

LongPistol::~LongPistol() = default;
