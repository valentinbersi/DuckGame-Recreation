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

void Sniper::onBulletCollision(CollisionObject* object) {
    if (object->layers().test(Layer::Index::Player))
        static_cast<Player*>(object)->damage();
}

void Sniper::update([[maybe_unused]] float delta) {
    if (bullet) {
        removeChild(bullet);
        bullet = nullptr;
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
                    gameObject::EventHandler<Sniper, CollisionObject*>::create(
                            getReference<Sniper>(), &Sniper::onBulletCollision));
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
