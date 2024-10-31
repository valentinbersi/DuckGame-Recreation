#include <memory>
#include <utility>

#include "CollisionObject.h"

#define DEFAULT_ROTATION 0
#define DEFAULT_COLLISION_LAYER 0
#define DEFAULT_COLLISION_MASK 0

CollisionObject::CollisionObject(Object* parent):
        CollisionObject(parent, Vector2::ZERO, DEFAULT_ROTATION, DEFAULT_COLLISION_LAYER,
                          DEFAULT_COLLISION_MASK, nullptr) {}

CollisionObject::CollisionObject(Object* parent, Vector2 position, const float rotation,
                                     const u32 collisionLayer, const u32 collisionMask,
                                     std::unique_ptr<Shape2D> shape):
        Object2D(parent, std::move(position), rotation),
        _collisionLayer(collisionLayer),
        _collisionMask(collisionMask),
        _shape(shape.release()) {
    registerEvent<CollisionObject, CollisionObject&>("bodyEntered");
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

void CollisionObject::collideWith(CollisionObject& other) {
    if ((_collisionMask & other.collisionLayer()) != 0 && _shape->intersects(*other._shape))
        fire<CollisionObject, CollisionObject&>("bodyEntered", other);
}
