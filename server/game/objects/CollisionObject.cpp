#include "CollisionObject.h"

#include <memory>
#include <utility>

CollisionObject::CollisionObject(Object* parent, Vector2 position, const float rotation,
                                 const u32 collisionLayer, const u32 collisionMask,
                                 std::unique_ptr<Shape2D> shape):
        Object2D(parent, std::move(position), rotation),
        _collisionLayer(collisionLayer),
        _collisionMask(collisionMask),
        _shape(shape.release()) {}

bool CollisionObject::collidesWith(const CollisionObject& other) const {
    return _shape->intersects(*other._shape);
}

CollisionObject::~CollisionObject() { delete _shape; }

void CollisionObject::updateInternal([[maybe_unused]] const float delta) {
    Object2D::updateInternal(delta);
    _shape->center(position());
}

u32 CollisionObject::collisionLayer() const { return _collisionLayer; }

u32 CollisionObject::collisionMask() const { return _collisionMask; }

CollisionObject& CollisionObject::setCollisionLayer(const u32 collisionLayer) noexcept {
    _collisionLayer = collisionLayer;
    return *this;
}

#define FIRST_BIT 1
#define MAX_LAYER 31
#define LAYER_OUT_OF_RANGE "layer must be between 0 and 32"

CollisionObject& CollisionObject::activateCollisionLayer(const u8 layer) {
    if (layer > MAX_LAYER)
        throw std::out_of_range(LAYER_OUT_OF_RANGE);

    _collisionLayer |= FIRST_BIT << layer;
    return *this;
}

CollisionObject& CollisionObject::deactivateCollisionLayer(const u8 layer) {
    if (layer > MAX_LAYER)
        throw std::out_of_range(LAYER_OUT_OF_RANGE);

    _collisionLayer &= UINT32_MAX ^ FIRST_BIT << layer;
    return *this;
}

CollisionObject& CollisionObject::setCollisionMask(const u32 collisionMask) noexcept {
    _collisionMask = collisionMask;
    return *this;
}

CollisionObject& CollisionObject::activateCollisionMask(const u8 layer) {
    if (layer > MAX_LAYER)
        throw std::out_of_range(LAYER_OUT_OF_RANGE);

    _collisionMask |= 1 << layer;
    return *this;
}

CollisionObject& CollisionObject::deactivateCollisionMask(const u8 layer) {
    if (layer > MAX_LAYER)
        throw std::out_of_range(LAYER_OUT_OF_RANGE);

    _collisionMask &= UINT32_MAX ^ 1 << layer;
    return *this;
}

#define EXPIRED_COLLISION_OBJECT "CollisionObject is expired"

void CollisionObject::registerCollision(std::weak_ptr<CollisionObject> collisionObject) {
    if (collisionObject.expired())
        throw std::invalid_argument(EXPIRED_COLLISION_OBJECT);

    objectsToCollide.push_front(std::move(collisionObject));
}

void CollisionObject::resetRegisteredCollisions() { objectsToCollide.clear(); }
