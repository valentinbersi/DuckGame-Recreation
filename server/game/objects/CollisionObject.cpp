#include "CollisionObject.h"

#include <memory>
#include <utility>

CollisionObject::CollisionObject(const CollisionObject& other):
        Object2D(other),
        _collisionLayer(other._collisionLayer),
        _collisionMask(other._collisionMask),
        _shape(other._shape->clone().release()) {}

CollisionObject& CollisionObject::operator=(const CollisionObject& other) {
    if (this == &other)
        return *this;

    Object2D::operator=(other);
    _collisionLayer = other._collisionLayer;
    _collisionMask = other._collisionMask;
    delete _shape;
    _shape = other._shape->clone().release();
    return *this;
}

CollisionObject::CollisionObject(CollisionObject&& other) noexcept:
        Object2D(std::move(other)),
        _collisionLayer(other._collisionLayer),
        _collisionMask(other._collisionMask),
        _shape(other._shape) {
    other._shape = nullptr;
}

CollisionObject& CollisionObject::operator=(CollisionObject&& other) noexcept {
    if (this == &other)
        return *this;

    Object2D::operator=(std::move(other));
    _collisionLayer = other._collisionLayer;
    _collisionMask = other._collisionMask;
    delete _shape;
    _shape = other._shape;
    other._shape = nullptr;
    return *this;
}

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

void CollisionObject::activateCollisionLayer(const u8 layer) { _collisionLayer |= 1 << layer; }

void CollisionObject::deactivateCollisionLayer(const u8 layer) {
    _collisionLayer &= UINT32_MAX ^ 1 << layer;
}

void CollisionObject::activateCollisionMask(const u8 layer) { _collisionMask |= 1 << layer; }

void CollisionObject::deactivateCollisionMask(const u8 layer) {
    _collisionMask &= UINT32_MAX ^ 1 << layer;
}

#define EXPIRED_COLLISION_OBJECT "CollisionObject is expired"

void CollisionObject::registerCollision(std::weak_ptr<CollisionObject> collisionObject) {
    if (collisionObject.expired())
        throw std::invalid_argument(EXPIRED_COLLISION_OBJECT);

    objectsToCollide.push_front(std::move(collisionObject));
}

void CollisionObject::resetRegisteredCollisions() { objectsToCollide.clear(); }
