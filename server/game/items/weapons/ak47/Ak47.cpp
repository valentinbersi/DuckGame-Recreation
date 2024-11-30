#include "Ak47.h"
#include "GameController.h"
#include "Player.h"
#include "Bullet.h"
#define BULLET_TO_MID_VARIATION 2
#define BULLET_TO_MAX_VARIATION 4

#define eventHandler(Function) \
    gameObject::EventHandler<Ak47>::create(getReference<Ak47>(), Function)

Ak47::Ak47(ItemID id, u8 ammo, Vector2 recoil, float reach, float minDispersion, float midDispersion, float maxDispersion, float timeBetweenShots):
        EquippableWeapon(id, ammo, std::move(recoil)),
        reach(reach),
        bulletsFired(0),   
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

Vector2 Ak47::generateDirection() {
    float variation; 
    if (bulletsFired < BULLET_TO_MID_VARIATION){
        variation = randomDispersionMin();
    } else if (bulletsFired < BULLET_TO_MAX_VARIATION){
        variation = randomDispersionMid();
    } else {
        variation = randomDispersionMax();
    }
    return (parent<Player>()->viewDirection() == DuckData::Direction::Right ? Vector2::RIGHT :
                                                                               Vector2::LEFT)
            .rotated(variation);
}

void Ak47::generateBullet() {
    auto bullet = std::make_unique<Bullet>(generateDirection(), reach);
    bullet->setGlobalPosition(
            parent<Player>()->globalPosition() +
                    (parent<Player>()->viewDirection() == DuckData::Direction::Right ?
                             Vector2::RIGHT * 2 :
                             Vector2::LEFT * 2),
            Force::Yes);

    getRoot<GameController>()->addToLevel("Bullet", std::move(bullet));
}

void Ak47::actionate() {
    if(delay){
        return;
    }

    if (fire()){
        generateBullet();
        delay = true;
        ++bulletsFired;
        timer->start();
    }
}

void Ak47::deactionate() { bulletsFired = 0;}

Ak47::~Ak47() = default;
