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
    std::cout << "RayCast: Start " << ray.start() << " End " << ray.end() << std::endl;
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

    fire(Events::Collision,
         std::ranges::min(collisions,
                          [this](const std::pair<Vector2, std::weak_ptr<CollisionObject>>& a,
                                 const std::pair<Vector2, std::weak_ptr<CollisionObject>>& b) {
                              return ray.start().distance(a.first) < ray.start().distance(b.first);
                          })
                 .second.lock()
                 .get());
}

void RayCast::clearCollisions() { objectsToCollide.clear(); }
