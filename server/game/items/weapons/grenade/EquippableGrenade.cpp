#include "EquippableGrenade.h"
#include "Player.h"


#define eventHandler(Function) \
    gameObject::EventHandler<EquippableGrenade>::create(getReference<EquippableGrenade>(), Function)

EquippableGrenade::EquippableGrenade(ItemID id, float timeToExplode) : 
    EquippableItem(id),
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
}

//Nothing to be done
void EquippableGrenade::deactionate() {}

EquippableGrenade::~EquippableGrenade() = default
