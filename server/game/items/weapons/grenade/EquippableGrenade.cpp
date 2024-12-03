#include "EquippableGrenade.h"
#include "Player.h"
#include "GameController.h"
#define GRENADE "Grenade"

#define eventHandler(Function) \
    gameObject::EventHandler<EquippableGrenade>::create(getReference<EquippableGrenade>(), Function)

EquippableGrenade::EquippableGrenade(ItemID id, u8 ammo,float timeToExplode) : 
    EquippableWeapon(id, ammo, Vector2::ZERO),
    timer(new GameTimer(timeToExplode)) {
        timer->connect(GameTimer::Events::Timeout, eventHandler(&EquippableGrenade::onTimeout));
        addChild("Timer", timer);
    }

void EquippableGrenade::onTimeout() {
    //creamos al nivel la explosion con getroot at to level.
    parent<Player>()->removeItem();
}

void EquippableGrenade::actionate() {
    if (!timer->started()){
        timer->start();
    }
    // float timeLeft = timer->getTimeLeft();
    timer->reset();
    // Vector2 direction = parent<Player>()->aimingDirection();
    // getRoot<GameController>()->addToLevel(GRENADE, std::make_unique<Grenade>(timeLeft));   
    --ammo_;
    if (ammo_ == INeedMoreBullets) {
        parent<Player>()->removeItem();
    }
}

//Nothing to be done
void EquippableGrenade::deactionate() {}

EquippableGrenade::~EquippableGrenade() = default;
