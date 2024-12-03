#include "Explosion.h"

#include "Box.h"
#include "Config.h"
#include "Layer.h"
#include "Player.h"

#define TIME_OF_EXPLOSION 0.75f
#define eventHandler(Function, ...) \
    gameObject::EventHandler<Explosion __VA_ARGS__>::create(getReference<Explosion>(), Function)

Explosion::Explosion(const Vector2& position):
        Area(position, Layer::None, Layer::Player | Layer::Box,
             Config::Weapons::Grenade::radius() * 2, Config::Weapons::Grenade::radius() * 2),
        timer(new GameTimer(TIME_OF_EXPLOSION)),
        hasFinished(false) {

    this->connect(Events::Collision, eventHandler(&Explosion::onCollision, , CollisionObject*));
    timer->connect(GameTimer::Events::Timeout, eventHandler(&Explosion::onTimeout));
    addChild("Timer", timer);
    timer->start();
}

void Explosion::onTimeout() { hasFinished = true; }

void Explosion::onCollision(CollisionObject* object) {
    if (object->layers().test(Layer::Index::Player)) {
        static_cast<Player*>(object)->damage();
    }
    if (object->layers().test(Layer::Index::Box)) {
        static_cast<Box*>(object)->onCollision();
    }
}

void Explosion::update([[maybe_unused]]float delta) {
    if (hasFinished) {
        parent()->removeChild(this);
    }
}

SizedObjectData Explosion::status() const { return SizedObjectData(getShape()); }

Explosion::~Explosion() = default;
