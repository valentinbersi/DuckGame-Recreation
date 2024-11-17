#include "PhysicsObject.h"

#include "GlobalPhysics.h"
#include "Math.h"

PhysicsObject::PhysicsObject(GameObject* parent, Vector2 position,
                             const std::bitset<LayersCount> layers,
                             const std::bitset<LayersCount> scannedLayers, const float width,
                             const float height, Vector2 initialVelocity, const Gravity gravity):
        CollisionObject(parent, std::move(position), layers, scannedLayers, width, height),
        _velocity(std::move(initialVelocity)),
        gravityAccumulator({0, 0}),
        gravity(gravity) {}

PhysicsObject::~PhysicsObject() = default;

void PhysicsObject::updateInternal(const float delta) {
    if (gravity == Gravity::Enabled)
        gravityAccumulator += GlobalPhysics::gravity;

    _velocity += gravityAccumulator * delta;
    CollisionObject::updateInternal(delta);
}

void PhysicsObject::processCollisions(const float delta) {
    if (Math::isEqualAprox(_velocity.lengthSquared(), 0))
        return;

    Vector2 velocityStep;

    if (Math::isLessAprox(_velocity.lengthSquared(), 4))
        velocityStep = _velocity;
    else
        velocityStep = _velocity.normalized() * 2;

    bool finishCollisions = false;
    Vector2 finalVelocity;

    for (Vector2 displaced = velocityStep;
         Math::isLessAprox(displaced.lengthSquared(), _velocity.lengthSquared()) and
         not finishCollisions;
         displaced += velocityStep) {

        for (const auto& object: objectsToCollide) {
            if (const auto objectPtr = object.lock(); objectPtr != nullptr) {
                std::optional collisionInfo(moveAndCollide(*objectPtr, velocityStep));

                if (not collisionInfo.has_value())
                    continue;

                velocityStep = collisionInfo->pushedPosition - position();
                if (Math::isGreaterAprox(collisionInfo->collisionNormal.y(), 0))
                    gravityAccumulator = {0, 0};

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
