#include "PhysicsObject.h"

#include <algorithm>
#include <memory>
#include <ranges>
#include <utility>
#include <vector>

#include "GlobalPhysics.h"
#include "Math.h"

PhysicsObject::PhysicsObject(const Vector2& position, const std::bitset<LayersCount> layers,
                             const std::bitset<LayersCount> scannedLayers, const float width,
                             const float height, const Gravity gravity, Vector2 initialVelocity,
                             const CollisionType collisionType):
        CollisionObject(position, layers, scannedLayers, width, height),
        gravity(gravity),
        collisionType(collisionType),
        _velocity(std::move(initialVelocity)),
        _onGround(false) {}

PhysicsObject::~PhysicsObject() = default;

void PhysicsObject::updateInternal(const float delta) {
    if (gravity == Gravity::Enabled)
        _velocity += GlobalPhysics::gravity * delta;

    CollisionObject::updateInternal(delta);
}

void PhysicsObject::processCollisions(const float delta) {
    _onGround = false;
    std::vector<std::pair<int, float>> collisionOrder;

    for (size_t i = 0; i < objectsToCollide.size(); ++i) {
        const std::shared_ptr objectPtr(objectsToCollide[i].lock());

        if (not objectPtr)
            continue;

        const std::optional collisionInfo(moveAndCollide(*objectPtr, _velocity, delta));

        if (not collisionInfo)
            continue;

        collisionOrder.emplace_back(i, collisionInfo->contactTime);
    }

    std::ranges::sort(collisionOrder,
                      [](const std::pair<int, float>& a, const std::pair<int, float>& b) {
                          return a.second < b.second;
                      });

    for (const int index: collisionOrder | std::views::keys) {
        const std::shared_ptr objectPtr(objectsToCollide[index].lock());

        if (not objectPtr)
            continue;

        const std::optional<IntersectionInfo> collisionInfo =
                moveAndCollide(*objectPtr, _velocity, delta);

        if (not collisionInfo)
            continue;

        if (collisionInfo->contact[2])
            _onGround = true;

        switch (collisionType) {
            case CollisionType::Stop:
                _velocity = Vector2::ZERO;
                break;
            case CollisionType::Slide:
                _velocity += collisionInfo->contactNormal *
                             Vector2(std::abs(_velocity.x()), std::abs(_velocity.y())) *
                             (1 - collisionInfo->contactTime);
                break;
            case CollisionType::Bounce:
                // TODO: implement
                break;

            default:;
        }

        fire(Events::Collision, objectPtr.get());
    }

    setPosition(position() + _velocity * delta);
}

void PhysicsObject::setGravity(const Gravity gravity) { this->gravity = gravity; }
