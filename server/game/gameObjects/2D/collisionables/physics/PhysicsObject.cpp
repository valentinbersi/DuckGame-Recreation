#include "PhysicsObject.h"

#include <memory>
#include <ranges>
#include <utility>
#include <vector>

#include "GlobalPhysics.h"
#include "Math.h"

PhysicsObject::PhysicsObject(GameObject* parent, const Vector2& position,
                             const std::bitset<LayersCount> layers,
                             const std::bitset<LayersCount> scannedLayers, const float width,
                             const float height, const Gravity gravity):
        CollisionObject(parent, position, layers, scannedLayers, width, height),
        gravity(gravity),
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

        const std::optional collisionInfo(moveAndCollide(*objectPtr, _velocity, delta));

        if (not collisionInfo)
            continue;

        if (collisionInfo->contactNormal.y() < 0)
            _onGround = true;

        _velocity += collisionInfo->contactNormal *
                     Vector2(std::abs(_velocity.x()), std::abs(_velocity.y())) *
                     (1 - collisionInfo->contactTime);
    }

    setPosition(position() + _velocity * delta);
}

void PhysicsObject::setGravity(const Gravity gravity) { this->gravity = gravity; }
