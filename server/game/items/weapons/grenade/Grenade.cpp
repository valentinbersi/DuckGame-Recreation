#include "Grenade.h"
#include "Config.h"
#include "Layer.h"
#include "GameController.h"
#include "Explosion.h"

#define INICIAL_VELOCITY 10,10
#define GRENADE_DIMENSIONS 1.25, 1.375

#define eventHandler(Function) \
    gameObject::EventHandler<Grenade>::create(getReference<Grenade>(), Function)

Grenade::Grenade(ItemID id, const Vector2 position, const Vector2 direction, float timeToExplode) :
        Item(GRENADE_DIMENSIONS, id, 0),
        timer(new GameTimer(timeToExplode)),
        hasExploded(false) {
    
    this->setGlobalPosition(position);
    this->setLayers(Layer::Item);
    this->setScannedLayers(Layer::Wall | Layer::Box);
    this->_velocity = Vector2(INICIAL_VELOCITY)*direction;
    timer->connect(GameTimer::Events::Timeout, eventHandler(&Grenade::onTimeout));
    timer->start();
}

void Grenade::onTimeout() {
    hasExploded = true;
}

void Grenade::update([[maybe_unused]]float delta) {
    if (hasExploded) {
        Vector2 explosionPosition = globalPosition();
        getRoot<GameController>()->addToLevel("Explosion", std::make_unique<Explosion>(globalPosition()));
        parent()->removeChild(this);
        return;
    }
    if (_velocity.x() > 0) {
        _velocity += Vector2::LEFT * 5 * delta;
    } else if (_velocity.x() < 0) {
        _velocity += Vector2::RIGHT * 5 * delta;
    }
}

Grenade::~Grenade() = default;