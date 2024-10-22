#include "CollisionObject2D.h"

#define DEFAULT_ROTATION 0
#define DEFAULT_COLLISION_LAYER 0
#define DEFAULT_COLLISION_MASK 0

CollisionObject2D::CollisionObject2D(Object* parent):
        CollisionObject2D(parent, Vector2::ZERO, DEFAULT_ROTATION, DEFAULT_COLLISION_LAYER,
                          DEFAULT_COLLISION_MASK) {

    registerEvent<CollisionObject2D&>("bodyEntered");
}

CollisionObject2D::CollisionObject2D(Object* parent, Vector2 position, const f32 rotation,
                                     const u32 collisionLayer,
                                     const u32 collisionMask /*, Shape2D shape*/):
        Object2D(parent, std::move(position), rotation),
        _collisionLayer(collisionLayer),
        _collisionMask(collisionMask) /*, _shape(std::move(shape))*/ {}

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
    bool isInScannedMask = _collisionMask & other.collisionLayer() != 0 ? true : false;

    // return _shape.contains(other._shape);

    emit<CollisionObject2D&>("bodyEntered", other);
}