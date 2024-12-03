#include "Sniper.h"

#include <utility>

#include "GameController.h"
#include "Layer.h"
#include "Player.h"
#include "RayCast.h"

#define eventHandler(Function) \
    gameObject::EventHandler<Sniper>::create(getReference<Sniper>(), Function)

Sniper::Sniper(const ItemID id, const u8 ammo, Vector2 recoil, const float reach,
               const float dispersion, const float reloadTime):
        ShootableGun(id, ammo, std::move(recoil)),
        reach(reach),
        firing(false),
        reloading(false),
        timer(new GameTimer(reloadTime)),
        bullet(nullptr),
        randomDispersionGenerator(-dispersion, dispersion) {
    timer->connect(GameTimer::Events::Timeout, eventHandler(&Sniper::setNotReloading));
    addChild("Timer", timer);
}

void Sniper::setNotReloading() {
    reloading = false;
    timer->reset();
}

void Sniper::update([[maybe_unused]] float delta) {
    if (!bullets.empty()) {
        removeChild(bullets.front());
        bullets.pop_front();
    }

    if (not fireNextFrame or reloading)
        return;

    if (not fire()) {
        fireNextFrame = false;
        return;
    }

    fireNextFrame = false;
    bullet = generateBullet(parent<Player>()->aimingDirection(), reach);
    bullet->connect(RayCast::Events::Collision,
                    gameObject::EventHandler<ShootableGun, CollisionObject*>::create(
                            getReference<ShootableGun>(), &ShootableGun::onBulletCollision));
    bullets.push_back(bullet);
    reloading = true;
    timer->start();
}

void Sniper::actionate() {
    if (firing || reloading)
        return;

    firing = true;
    fireNextFrame = true;
}

void Sniper::deactionate() {
    firing = false;
    fireNextFrame = false;
}

Sniper::~Sniper() = default;
