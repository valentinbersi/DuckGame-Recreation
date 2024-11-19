#include "PhysicsObject.h"

#include "GlobalPhysics.h"
#include "Math.h"

PhysicsObject::PhysicsObject(GameObject* parent, const Vector2& position,
                             const std::bitset<LayersCount> layers,
                             const std::bitset<LayersCount> scannedLayers, const float width,
                             const float height, const Gravity gravity):
        CollisionObject(parent, position, layers, scannedLayers, width, height), gravity(gravity) {}

PhysicsObject::~PhysicsObject() = default;

void PhysicsObject::updateInternal(const float delta) {
    if (gravity == Gravity::Enabled)
        _velocity += GlobalPhysics::gravity * delta;

    CollisionObject::updateInternal(delta);
}

void PhysicsObject::processCollisions(const float delta) {
    _onGround = false;
    std::vector<std::pair<int, float>> collisionOrder;

    for (size_t i = 0; i < objectsToCollide.size(); ++i)
        if (const std::shared_ptr<CollisionObject> objectPtr = objectsToCollide[i].lock())
            if (const std::optional<IntersectionInfo> collisionInfo =
                        moveAndCollide(*objectPtr, _velocity, delta))
                collisionOrder.emplace_back(i, collisionInfo->tHitNear);

    std::ranges::sort(collisionOrder,
                      [](const std::pair<int, float>& a, const std::pair<int, float>& b) {
                          return a.second < b.second;
                      });

    for (const auto& [index, _]: collisionOrder) {
        if (const std::shared_ptr<CollisionObject> objectPtr = objectsToCollide[index].lock()) {
            if (const std::optional<IntersectionInfo> collisionInfo =
                        moveAndCollide(*objectPtr, _velocity, delta)) {
                if (collisionInfo->contactNormal.y() < 0) {
                    _onGround = true;
                }
                _velocity += collisionInfo->contactNormal *
                             Vector2(std::abs(_velocity.x()), std::abs(_velocity.y())) *
                             (1 - collisionInfo->tHitNear);
            }
        }
    }

    setPosition(position() + _velocity * delta);
}

void PhysicsObject::setGravity(const Gravity gravity) { this->gravity = gravity; }
