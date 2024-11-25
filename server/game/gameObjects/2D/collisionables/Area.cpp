#include "Area.h"

#include <memory>
#include <string>

Area::Area(const Vector2& position, const std::bitset<LayersCount> layers,
           const std::bitset<LayersCount> scannedLayers, const float width, const float height):
        CollisionObject(position, layers, scannedLayers, width, height) {}

void Area::start() {}

void Area::update([[maybe_unused]] float delta) {}

void Area::processCollisions([[maybe_unused]] const float delta) {
    for (auto& object: objectsToCollide) {
        if (const std::shared_ptr ownedObject(object.lock());
            ownedObject != nullptr && collidesWith(*ownedObject))
            fire(Events::Collision, ownedObject.get());
    }
}
