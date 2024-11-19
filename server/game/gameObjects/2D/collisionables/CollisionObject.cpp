#include "CollisionObject.h"

#include <memory>
#include <utility>
#include <vector>

#define NULL_SHAPE "Shape cannot be null"

CollisionObject::CollisionObject(GameObject* parent, const Vector2& position,
                                 const std::bitset<LayersCount> layers,
                                 const std::bitset<LayersCount> scannedLayers, const float width,
                                 const float height):
        GameObject2D(parent, position),
        _layers(layers),
        _scannedLayers(scannedLayers),
        shape(position, width, height) {}

bool CollisionObject::collidesWith(const CollisionObject& other) const {
    return shape.overlaps(other.shape);
}

std::optional<IntersectionInfo> CollisionObject::moveAndCollide(const CollisionObject& other,
                                                                const Vector2& displacement,
                                                                const float delta) const {
    return shape.overlaps(other.shape, displacement, delta);
}

CollisionObject::~CollisionObject() = default;

void CollisionObject::updateInternal([[maybe_unused]] const float delta) {
    GameObject2D::updateInternal(delta);
}

GameObject2D& CollisionObject::setPosition(Vector2 position) noexcept {
    shape.setCenter(position);
    return GameObject2D::setPosition(std::move(position));
}

std::bitset<CollisionObject::LayersCount> CollisionObject::layers() const { return _layers; }

std::bitset<CollisionObject::LayersCount> CollisionObject::scannedLayers() const {
    return _scannedLayers;
}

CollisionObject& CollisionObject::setLayers(const std::bitset<LayersCount> layers) noexcept {
    _layers = layers;
    return *this;
}


CollisionObject& CollisionObject::addToLayer(const u8 layer) {
    _layers.set(layer);
    return *this;
}

CollisionObject& CollisionObject::removeFromLayer(const u8 layer) {
    _layers.reset(layer);
    return *this;
}

CollisionObject& CollisionObject::setScannedLayers(
        const std::bitset<LayersCount> scannedLayers) noexcept {

    _scannedLayers = scannedLayers;
    return *this;
}

CollisionObject& CollisionObject::addLayerToScan(const u8 layer) {
    _scannedLayers.set(layer);
    return *this;
}

CollisionObject& CollisionObject::removeLayerToScan(const u8 layer) {
    _scannedLayers.reset(layer);
    return *this;
}

#define EXPIRED_COLLISION_OBJECT "CollisionObject is expired"

void CollisionObject::registerCollision(std::weak_ptr<CollisionObject> collisionObject) {
    if (collisionObject.expired())
        throw std::invalid_argument(EXPIRED_COLLISION_OBJECT);

    if ((_scannedLayers & collisionObject.lock()->_layers).any())
        objectsToCollide.push_back(std::move(collisionObject));
}

void CollisionObject::resetRegisteredCollisions() { objectsToCollide.clear(); }
