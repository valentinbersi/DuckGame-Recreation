#include "PhysicsObject.h"

#include "GlobalPhysics.h"
#include "Math.h"

PhysicsObject::PhysicsObject(GameObject* parent, Vector2 position,
                             const std::bitset<LayersCount> layers,
                             const std::bitset<LayersCount> scannedLayers, const float width,
                             const float height, Vector2 initialVelocity, const Gravity gravity):
        CollisionObject(parent, std::move(position), layers, scannedLayers, width, height),
        _velocity(std::move(initialVelocity)),
        gravity(gravity) {}

PhysicsObject::~PhysicsObject() = default;

void PhysicsObject::updateInternal(const float delta) {
    if (gravity == Gravity::Enabled)
        _velocity += GlobalPhysics::gravity * delta;

    CollisionObject::updateInternal(delta);
}

void PhysicsObject::processCollisions([[maybe_unused]] const float delta) {
    for (const auto& object: objectsToCollide) {
        if (const auto objectPtr = object.lock(); objectPtr != nullptr) {
            std::optional newVelocity(moveAndCollide(*objectPtr, _velocity));

            if (not newVelocity.has_value())
                continue;

            _velocity = newVelocity.value();
        }
    }

    setPosition(position() + _velocity * delta);
}

const Vector2& PhysicsObject::velocity() const { return _velocity; }

void PhysicsObject::setVelocity(Vector2 velocity) { _velocity = std::move(velocity); }

void PhysicsObject::setGravity(const Gravity gravity) { this->gravity = gravity; }
