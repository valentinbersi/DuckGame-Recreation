#include "CollisionObject.h"

#include <memory>
#include <utility>

#define NULL_SHAPE "Shape cannot be null"

CollisionObject::CollisionObject(GameObject* parent, Vector2 position,
                                 const std::bitset<LAYERS_COUNT> layers,
                                 const std::bitset<LAYERS_COUNT> scannedLayers,
                                 std::unique_ptr<Shape2D> shape):
        GameObject2D(parent, std::move(position)),
        _layers(layers),
        _scannedLayers(scannedLayers),
        shape(shape.release()) {

    if (this->shape == nullptr)
        throw std::invalid_argument(NULL_SHAPE);
}

bool CollisionObject::collidesWith(const CollisionObject& other) const {
    return shape->intersects(*other.shape);
}

std::optional<IntersectionInfo> CollisionObject::moveAndCollide(const CollisionObject& other,
                                                                const Vector2& displacement) const {
    return shape->intersects(*other.shape, displacement);
}

CollisionObject::~CollisionObject() { delete shape; }

void CollisionObject::updateInternal([[maybe_unused]] const float delta) {
    GameObject2D::updateInternal(delta);
    shape->setCenter(position());
}

std::bitset<CollisionObject::LAYERS_COUNT> CollisionObject::layers() const { return _layers; }

std::bitset<CollisionObject::LAYERS_COUNT> CollisionObject::scannedLayers() const {
    return _scannedLayers;
}

CollisionObject& CollisionObject::setLayers(const std::bitset<LAYERS_COUNT> layers) noexcept {
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
        const std::bitset<LAYERS_COUNT> scannedLayers) noexcept {

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
        objectsToCollide.push_front(std::move(collisionObject));
}

void CollisionObject::resetRegisteredCollisions() { objectsToCollide.clear(); }
