#include "Banana.h"
#include "Layer.h"
#include "Player.h"


#define eventHandler(Function) \
    gameObject::EventHandler<Grenade>::create(getReference<Grenade>(), Function)
Banana::Banana(ItemID id, const Vector2 position, const Vector2 direction):
        Item({1.25, 1.375}, id, 0),
        wasSteped(false) {
    this->setGlobalPosition(position);
    this->setLayers(Layer::Item);
    this->setScannedLayers(Layer::Wall | Layer::Box);
    this->_velocity = direction*30 + Vector2::UP*20;
    this->connect(Collision::Events::Collision, eventHandler(&Banana::onCollision));
}

void Banana::onCollision(CollisionObject* obj) {
    if (obj->layers().test(Layer::Index::Wall)){
        _velocity = Vector2::ZERO;
        return;
    
    }
    if (obj->layers().test(Layer::Index::Player)){
        static_cast<Player*>(obj)->bananaEfect();
    }
    wasSteped = true;
}

void Banana::update(float delta) {
    if (wasSteped) {
        Vector2 explosionPosition = globalPosition();
        getRoot<GameController>()->addToLevel("Explosion", std::make_unique<Explosion>(globalPosition()));
        parent()->removeChild(this);
        return;
    }
    if (_velocity.x() > 0) {
        _velocity += Vector2::LEFT * 10 * delta;
    } else if (_velocity.x() < 0) {
        _velocity += Vector2::RIGHT * 10 * delta;
    }
}

Banana::~Banana() = default;
