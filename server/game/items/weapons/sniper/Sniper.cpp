
#include "Sniper.h"
#include "Player.h"
#include "Bullet.h"
#include "GameController.h"

#define eventHandler(                                          \
        Function)                                               \
    gameObject::EventHandler<Sniper>::create(getReference<Sniper>(), Function)

Sniper::Sniper(ItemID id, u8 ammo, Vector2 recoil, float reach, float dispersion, float reloadTime):
        EquippableWeapon(id, ammo, std::move(recoil)),
        reach(reach),
        firing(false),
        reloading(false),
        timer(new GameTimer(reloadTime)),
        randomGenerator(-dispersion, dispersion) {}

void Sniper::setNotReloading() {
    reloading = false;
}

void Sniper::generateBullet() {
    auto bullet = std::make_unique<Bullet>(Vector2::RIGHT, reach);
    bullet->setGlobalPosition(
            parent<Player>()->globalPosition() +
                    (parent<Player>()->viewDirection() == DuckData::Direction::Right ?
                            Vector2::RIGHT * 2 :
                            Vector2::LEFT * 2),
            Force::Yes);

    getRoot<GameController>()->addToLevel("Bullet", std::move(bullet));
}

void Sniper::actionate() {
    if (firing || reloading){
        return;
    }
    firing = true;
    if (fire()){
        generateBullet();
        reloading = true;
        timer->start();
    }
}

void Sniper::deactionate() { firing = false; }

Sniper::~Sniper() = default;
