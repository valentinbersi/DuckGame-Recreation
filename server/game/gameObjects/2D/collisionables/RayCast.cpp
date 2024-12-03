#include "RayCast.h"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#include "RayCast.h"

RayCast::RayCast(Vector2 start, Vector2 end, const std::bitset<LayersCount> scannedLayers):
        ray(std::move(start), std::move(end)), scannedLayers(scannedLayers) {
    registerEvent<CollisionObject*>(Events::Collision);
}

RayCast::RayCast(Vector2 start, const Vector2& direction, const float length,
                 const std::bitset<LayersCount> scannedLayers):
        ray(std::move(start), start + direction.normalized() * length),
        scannedLayers(scannedLayers) {
    registerEvent<CollisionObject*>(Events::Collision);
}

void RayCast::registerCollisions(std::weak_ptr<CollisionObject> object) {
    if ((scannedLayers & object.lock()->layers()).any())
        objectsToCollide.push_front(std::move(object));
}

void RayCast::processCollisions() {
    std::vector<std::pair<Vector2, std::weak_ptr<CollisionObject>>> collisions;
    for (const auto& object: objectsToCollide) {
        std::vector<Vector2> intersectionPoints =
                object.lock()->getShape().intersectionPointsWith(ray);

        if (intersectionPoints.empty())
            continue;

        collisions.emplace_back(std::ranges::min(intersectionPoints,
                                                 [this](const Vector2& a, const Vector2& b) {
                                                     return ray.start().distance(a) <
                                                            ray.start().distance(b);
                                                 }),
                                object);
    }

    if (collisions.empty())
        return;

    auto comparision = [this](const std::pair<Vector2, std::weak_ptr<CollisionObject>>& a,
                              const std::pair<Vector2, std::weak_ptr<CollisionObject>>& b) {
        return ray.start().distance(a.first) < ray.start().distance(b.first);
    };

    CollisionObject* closestObject = std::ranges::min(collisions, comparision).second.lock().get();

    fire(Events::Collision, closestObject);
}

void RayCast::clearCollisions() { objectsToCollide.clear(); }

Segment2D RayCast::getSegment() const { return ray; }
