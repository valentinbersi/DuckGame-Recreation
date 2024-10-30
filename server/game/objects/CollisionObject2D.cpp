#include "CollisionObject2D.h"

#include <memory>
#include <utility>

#define DEFAULT_ROTATION 0
#define DEFAULT_COLLISION_LAYER 0
#define DEFAULT_COLLISION_MASK 0

CollisionObject2D::CollisionObject2D(Object* parent):
        CollisionObject2D(parent, Vector2::ZERO, DEFAULT_ROTATION, DEFAULT_COLLISION_LAYER,
                          DEFAULT_COLLISION_MASK, nullptr) {}

CollisionObject2D::CollisionObject2D(Object* parent, Vector2 position, const float rotation,
                                     const u32 collisionLayer, const u32 collisionMask,
                                     std::unique_ptr<Shape2D> shape):
        Object2D(parent, std::move(position), rotation),
        _collisionLayer(collisionLayer),
        _collisionMask(collisionMask),
        _shape(shape.release()) {
    registerEvent<CollisionObject2D&>("bodyEntered");
}

u32 CollisionObject2D::collisionLayer() const { return _collisionLayer; }

u32 CollisionObject2D::collisionMask() const { return _collisionMask; }

void CollisionObject2D::activateCollisionLayer(const u8 layer) { _collisionLayer |= 1 << layer; }

void CollisionObject2D::deactivateCollisionLayer(const u8 layer) {
    _collisionLayer &= UINT32_MAX ^ 1 << layer;
}

void CollisionObject2D::activateCollisionMask(const u8 layer) { _collisionMask |= 1 << layer; }

void CollisionObject2D::deactivateCollisionMask(const u8 layer) {
    _collisionMask &= UINT32_MAX ^ 1 << layer;
}

void CollisionObject2D::collideWith(CollisionObject2D& other) {
    if ((_collisionMask & other.collisionLayer()) != 0 && _shape->intersects(*other._shape))
        fire<CollisionObject2D&>("bodyEntered", other);
}
