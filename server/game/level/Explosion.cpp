#include "Explosion.h"
#include "Layer.h"
#include "Config.h"
#include "Player.h"
#include "Box.h"

#define TIME_OF_EXPLOSION  1.5f
#define eventHandler(Function, ...) \
    gameObject::EventHandler<Explosion __VA_ARGS__>::create(getReference<Explosion>(), Function)

Explosion::Explosion(const Vector2& position) :
        Area(position, Layer::None, Layer::Player | Layer::Box, 
            Config::Weapons::Grenade::radius()*2, Config::Weapons::Grenade::radius()*2),
        timer(new GameTimer(TIME_OF_EXPLOSION)) {

    this->connect(Events::Collision, eventHandler(&Explosion::onCollision, , CollisionObject*));
    timer->connect(GameTimer::Events::Timeout, eventHandler(&Explosion::onTimeout));
    addChild("Timer", timer);
}   

void Explosion::onTimeout() {
    parent()->removeChild(this);
}

void Explosion::onCollision(CollisionObject* object) {
    if (object->layers().test(Layer::Player)) {
        static_cast<Player*>(object)->damage();
    }
    if (object->layers().test(Layer::Box)) {
        static_cast<Box*>(object)->onCollision();
    }
}

SizedObjectData Explosion::status() const {
    return SizedObjectData(getShape());
}

Explosion::~Explosion() = default;
