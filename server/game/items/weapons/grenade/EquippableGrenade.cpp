#include "EquippableGrenade.h"

#include "GameController.h"
#include "Player.h"
#include "Explosion.h"
#include "Grenade.h"
#define GRENADE "Grenade"

#define eventHandler(Function) \
    gameObject::EventHandler<EquippableGrenade>::create(getReference<EquippableGrenade>(), Function)

EquippableGrenade::EquippableGrenade(ItemID id, u8 ammo, float timeToExplode):
        EquippableWeapon(id, ammo, Vector2::ZERO), 
        timer(new GameTimer(timeToExplode)), 
        hasExploded(false),
        Pressed(false){
    timer->connect(GameTimer::Events::Timeout, eventHandler(&EquippableGrenade::onTimeout));
    addChild("Timer", timer);
    timer->reset();
}

void EquippableGrenade::onTimeout() {
    hasExploded = true;
}

void EquippableGrenade::actionate() {
    if (!timer->started()) {
        timer->start();
        Pressed = true;
        return;
    }
    if (Pressed){
        return;
    }
    Pressed = true;
    float timeLeft = timer->getTimeLeft();
    timer->reset();
    Vector2 direction = parent<Player>()->aimingDirection();
    Vector2 inicialPosition = parent<Player>()->globalPosition();
    getRoot<GameController>()->addToLevel(GRENADE, std::make_unique<Grenade>(ItemID::Grenade, inicialPosition, direction, timeLeft ));
    --ammo_;
}

void EquippableGrenade::update([[maybe_unused]]float delta){
    if(hasExploded){
        Vector2 explosionPosition = parent<Player>()->globalPosition();
        getRoot<GameController>()->addToLevel(GRENADE, std::make_unique<Explosion>(explosionPosition));
        parent<Player>()->removeItem();
        return;
    }
    if (ammo_ == INeedMoreBullets) {
        parent<Player>()->removeItem();
    }
}

void EquippableGrenade::deactionate() { Pressed = false;}

EquippableGrenade::~EquippableGrenade() = default;
