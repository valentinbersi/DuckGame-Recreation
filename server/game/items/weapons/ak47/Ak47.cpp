#include "Ak47.h"

#include <utility>

#include "GameController.h"
#include "Layer.h"
#include "Player.h"
#include "RayCast.h"

#define BULLET_TO_MID_VARIATION 2
#define BULLET_TO_MAX_VARIATION 4

#define eventHandler(Function) \
    gameObject::EventHandler<Ak47>::create(getReference<Ak47>(), Function)

Ak47::Ak47(const ItemID id, const u8 ammo, Vector2 recoil, const float reach,
           const float minDispersion, const float midDispersion, const float maxDispersion,
           const float timeBetweenShots):
        ShootableGun(id, ammo, std::move(recoil)),
        reach(reach),
        delay(false),
        bulletsFired(0),
        fireNextFrame(false),
        bullet(nullptr),
        randomDispersionMin(-minDispersion, maxDispersion),
        randomDispersionMid(-midDispersion, midDispersion),
        randomDispersionMax(-maxDispersion, maxDispersion),
        timer(new GameTimer(timeBetweenShots)) {
    timer->connect(GameTimer::Events::Timeout, eventHandler(&Ak47::onTimeOut));
    addChild("Timer", timer);
}

void Ak47::onTimeOut() {
    delay = false;
    timer->reset();
}

void Ak47::update([[maybe_unused]] float delta) {
    using gameObject::EventHandler;

    if (!bullets.empty()) {
        removeChild(bullets.front());
        bullets.pop_front();
    }

    if (delay or not fireNextFrame)
        return;

    if (not fire()) {
        fireNextFrame = false;
        return;
    }

    fireNextFrame = false;
    bullet = generateBullet(generateDirection(), reach);
    bullet->connect(RayCast::Events::Collision,
                    EventHandler<ShootableGun, CollisionObject*>::create(
                            getReference<ShootableGun>(), &ShootableGun::onBulletCollision));
    bullets.push_back(bullet);
    delay = true;
    ++bulletsFired;
    timer->start();
}

Vector2 Ak47::generateDirection() {
    float variation;

    if (bulletsFired < BULLET_TO_MID_VARIATION)
        variation = randomDispersionMin();

    else if (bulletsFired < BULLET_TO_MAX_VARIATION)
        variation = randomDispersionMid();

    else
        variation = randomDispersionMax();

    return parent<Player>()->aimingDirection().rotated(variation);
}

void Ak47::actionate() { fireNextFrame = true; }

void Ak47::deactionate() {
    bulletsFired = 0;
    fireNextFrame = false;
}

Ak47::~Ak47() = default;
