#include "PhysicsObject.h"

#include "GlobalPhysics.h"

PhysicsObject::PhysicsObject(const PhysicsObject& other):
        CollisionObject(other),
        _velocity(other._velocity),
        prevPosition(other.prevPosition),
        gravity(other.gravity) {}

PhysicsObject& PhysicsObject::operator=(const PhysicsObject& other) {
    if (this == &other)
        return *this;

    CollisionObject::operator=(other);
    _velocity = other._velocity;
    prevPosition = other.prevPosition;
    gravity = other.gravity;
    return *this;
}

PhysicsObject::PhysicsObject(PhysicsObject&& other) noexcept:
        CollisionObject(std::move(other)),
        _velocity(std::move(other._velocity)),
        prevPosition(std::move(prevPosition)),
        gravity(other.gravity) {

    other.gravity = Gravity::Disabled;
}

PhysicsObject& PhysicsObject::operator=(PhysicsObject&& other) noexcept {
    if (this == &other)
        return *this;

    CollisionObject::operator=(std::move(other));
    _velocity = std::move(other._velocity);
    prevPosition = std::move(other.prevPosition);
    gravity = other.gravity;
    other.gravity = Gravity::Disabled;
    return *this;
}

PhysicsObject::PhysicsObject(Object* parent, Vector2 position, const float rotation,
                             const u32 collisionLayer, const u32 collisionMask,
                             std::unique_ptr<Shape2D> shape, Vector2 initialVelocity,
                             const Gravity gravity):
        CollisionObject(parent, std::move(position), rotation, collisionLayer, collisionMask,
                        std::move(shape)),
        _velocity(std::move(initialVelocity)),
        gravity(gravity) {}

void PhysicsObject::moveAndCollide() {
    prevPosition = position();
    setPosition(position() + _velocity);
}

PhysicsObject::~PhysicsObject() = default;

const Vector2& PhysicsObject::velocity() const { return _velocity; }

void PhysicsObject::setVelocity(Vector2 velocity) { _velocity = std::move(velocity); }

void PhysicsObject::setGravity(const Gravity gravity) { this->gravity = gravity; }

void PhysicsObject::updateInternal(const float delta) {
    if (gravity == Gravity::Enabled)
        _velocity += GlobalPhysics::gravity;

    CollisionObject::updateInternal(delta);
}