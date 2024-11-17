#include "Area.h"

Area::Area(GameObject* parent, Vector2 position, const std::bitset<LayersCount> layers,
           const std::bitset<LayersCount> scannedLayers, const float width, const float height):
        CollisionObject(parent, std::move(position), layers, scannedLayers, width, height) {
    registerEvent<CollisionObject*>(eventName(Events::COLLISION));
}

void Area::start() {}

void Area::update([[maybe_unused]] float delta) {}

void Area::updateInternal(const float delta) { CollisionObject::updateInternal(delta); }

void Area::registerCollision(std::weak_ptr<CollisionObject> collisionObject) {
    CollisionObject::registerCollision(std::move(collisionObject));
}

void Area::processCollisions([[maybe_unused]] const float delta) {
    for (auto& object: objectsToCollide) {
        if (const std::shared_ptr ownedObject(object.lock());
            ownedObject != nullptr && collidesWith(*ownedObject))
            fire(eventName(Events::COLLISION), ownedObject.get());
    }
}

GameStatus Area::status() { return {}; }

#define COLLISION_NAME "Collision"

std::string Area::eventName(const Events eventType) {
    switch (eventType) {
        case Events::COLLISION:
            return "Collision";
        default:
            throw std::invalid_argument(INVALID_EVENT_TYPE);
    }
}
