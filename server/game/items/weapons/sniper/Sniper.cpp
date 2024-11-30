
#include "Sniper.h"

#include <memory>
#include <utility>
#include "Math.h"

#include "Bullet.h"
#include "GameController.h"
#include "Player.h"

#define eventHandler(Function) \
    gameObject::EventHandler<Sniper>::create(getReference<Sniper>(), Function)

Sniper::Sniper(ItemID id, u8 ammo, Vector2 recoil, float reach, float dispersion, float reloadTime):
        EquippableWeapon(id, ammo, std::move(recoil)),
        reach(reach),
        firing(false),
        reloading(false),
        timer(new GameTimer(reloadTime)),
        randomDispersionGenerator(-dispersion ,dispersion) {
            timer->connect(GameTimer::Events::Timeout, eventHandler(&Sniper::setNotReloading));
            addChild("Timer", timer);
        }

void Sniper::setNotReloading() { 
    reloading = false;
    timer->reset(); 
}

void Sniper::generateBullet() {
    const Vector2 direction =
            (parent<Player>()->viewDirection() == DuckData::Direction::Right ? Vector2::RIGHT :
                                                                               Vector2::LEFT)
                    .rotated(randomDispersionGenerator());
    auto bullet = std::make_unique<Bullet>(direction, reach);
    bullet->setGlobalPosition(
            parent<Player>()->globalPosition() +
                    (parent<Player>()->viewDirection() == DuckData::Direction::Right ?
                             Vector2::RIGHT * 2 :
                             Vector2::LEFT * 2),
            Force::Yes);

    getRoot<GameController>()->addToLevel("Bullet", std::move(bullet));
}

void Sniper::actionate() {
    if (firing || reloading) {
        return;
    }
    firing = true;
    if (fire()) {
        generateBullet();
        reloading = true;
        timer->start();
    }
}

void Sniper::deactionate() { firing = false; }

Sniper::~Sniper() = default;
