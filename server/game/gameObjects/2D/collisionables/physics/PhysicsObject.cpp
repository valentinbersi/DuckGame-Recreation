#include "PhysicsObject.h"

#include "GlobalPhysics.h"

PhysicsObject::PhysicsObject(GameObject* parent, Vector2 position,
                             const std::bitset<LAYERS_COUNT> layers,
                             const std::bitset<LAYERS_COUNT> scannedLayers,
                             std::unique_ptr<Shape2D> shape, Vector2 initialVelocity,
                             Vector2 initialAcceleration, const Gravity gravity):

        CollisionObject(parent, std::move(position), layers, scannedLayers, std::move(shape)),
        _velocity(std::move(initialVelocity)),
        acceleration(std::move(initialAcceleration)),
        gravity(gravity) {}

PhysicsObject::~PhysicsObject() = default;

void PhysicsObject::updateInternal(const float delta) {
    if (gravity == Gravity::Enabled)
        acceleration += GlobalPhysics::gravity;

    _velocity += acceleration * delta;
    CollisionObject::updateInternal(delta);
}

void PhysicsObject::processCollisions(const float delta) {
    Vector2 finalVelocity;
    Vector2 velocityStep = _velocity / (_velocity.lengthSquared() / 4);
    bool finishCollisions = false;

    for (Vector2 displaced = velocityStep;
         displaced.lengthSquared() < _velocity.lengthSquared() and not finishCollisions;
         displaced += velocityStep) {
        for (const auto& object: objectsToCollide) {
            if (const auto objectPtr = object.lock(); objectPtr != nullptr) {
                std::optional collisionInfo(moveAndCollide(*objectPtr, velocityStep));

                if (not collisionInfo.has_value())
                    continue;

                velocityStep = collisionInfo->nextPosition - position();
                finishCollisions = true;
            }
        }

        finalVelocity += velocityStep;
    }

    setPosition(position() + finalVelocity * delta);
}

const Vector2& PhysicsObject::velocity() const { return _velocity; }

void PhysicsObject::setVelocity(Vector2 velocity) { _velocity = std::move(velocity); }

void PhysicsObject::setGravity(const Gravity gravity) { this->gravity = gravity; }
