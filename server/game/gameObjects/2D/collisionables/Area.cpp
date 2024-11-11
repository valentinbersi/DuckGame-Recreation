#include "Area.h"

Area::Area(GameObject* parent, Vector2 position, const float rotation,
           const std::bitset<LAYERS_COUNT> layers, const std::bitset<LAYERS_COUNT> scannedLayers,
           std::unique_ptr<Shape2D> shape):
        CollisionObject(parent, std::move(position), rotation, layers, scannedLayers,
                        std::move(shape)) {
    registerEvent<CollisionObject*>(eventName(Events::COLLISION));
}

void Area::start() {}

void Area::update([[maybe_unused]] float delta) {}

void Area::updateInternal(const float delta) { CollisionObject::updateInternal(delta); }

void Area::registerCollision(std::weak_ptr<CollisionObject> collisionObject) {
    CollisionObject::registerCollision(std::move(collisionObject));
}

void Area::processCollisions() {
    for (auto& object: objectsToCollide) {
        if (const std::shared_ptr ownedObject(object.lock());
            ownedObject != nullptr && collidesWith(*ownedObject))
            fire<CollisionObject*>(eventName(Events::COLLISION), ownedObject.get());
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
