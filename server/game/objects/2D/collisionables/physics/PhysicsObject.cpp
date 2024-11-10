#include "PhysicsObject.h"

#include "GlobalPhysics.h"

PhysicsObject::PhysicsObject(Object* parent, Vector2 position, const float rotation,
                             const std::bitset<LAYERS_COUNT> layers,
                             const std::bitset<LAYERS_COUNT> scannedLayers,
                             std::unique_ptr<Shape2D> shape, Vector2 initialVelocity,
                             const Gravity gravity):

        CollisionObject(parent, std::move(position), rotation, layers, scannedLayers,
                        std::move(shape)),
        _velocity(std::move(initialVelocity)),
        gravity(gravity) {}

PhysicsObject::~PhysicsObject() = default;

void PhysicsObject::updateInternal(const float delta) {
    if (gravity == Gravity::Enabled)
        _velocity += GlobalPhysics::gravity;

    CollisionObject::updateInternal(delta);
}

void PhysicsObject::processCollisions() {
    std::ranges::for_each(objectsToCollide, [this](const std::weak_ptr<CollisionObject>& object) {
        if (const auto objectPtr = object.lock();
            objectPtr != nullptr && collidesWith(*objectPtr)) {
            _velocity = Vector2::ZERO;
        }
    });

    setPosition(position() + _velocity);
}

const Vector2& PhysicsObject::velocity() const { return _velocity; }

void PhysicsObject::setVelocity(Vector2 velocity) { _velocity = std::move(velocity); }

void PhysicsObject::setGravity(const Gravity gravity) { this->gravity = gravity; }