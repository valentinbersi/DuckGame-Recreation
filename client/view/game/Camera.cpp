#include "Camera.h"

Camera::Camera(int& windowWidth, int& windowHeight):
        windowWidth(windowWidth),
        windowHeight(windowHeight),
        viewRect(Vector2::ZERO, {0, 0}),
        ducksArrived(false) {}

void Camera::update(const std::list<DuckData>& ducks, const float deltaTime) {
    auto [center, maxDistance, aspectRatio] = updateInfo(ducks);
    updateZoom(center, maxDistance, aspectRatio, deltaTime);

    if (not ducks.empty())
        ducksArrived = true;
}

void Camera::forceUpdate(const std::list<DuckData>& ducks) {
    auto [center, maxDistance, aspectRatio] = updateInfo(ducks);
    updateZoom(center, maxDistance, aspectRatio, 1, Force::Yes);

    if (not ducks.empty())
        ducksArrived = true;
}

#define CAMERA_SPEED 2

void Camera::updateZoom(const Vector2& center, const Vector2& maxDistance, const float aspectRatio,
                        const float deltaTime, const Force force) {
    const Vector2 rectDimension = maxDistance.x() > maxDistance.y() ?
                                          Vector2(maxDistance.x(), maxDistance.x() / aspectRatio) :
                                          Vector2(maxDistance.y() * aspectRatio, maxDistance.y());

    if (not ducksArrived) {
        viewRect.setSize(rectDimension);
        viewRect.setCenter(center);
        return;
    }

    if (force == Force::Yes)
        viewRect.setSize(rectDimension);
    else
        viewRect.setSize(viewRect.size() +
                         (rectDimension - viewRect.size()) * CAMERA_SPEED * deltaTime);

    viewRect.setCenter(viewRect.center() + (center - viewRect.center()) * CAMERA_SPEED * deltaTime);
}

Camera::UpdateInfo Camera::updateInfo(const std::list<DuckData>& ducks) const {
    UpdateInfo info;
    info.aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
    info.center = centerOfDucks(ducks);
    info.maxDistance = calculateMaxDistance(ducks, info.aspectRatio);
    return info;
}

Vector2 Camera::calculateMaxDistance(const std::list<DuckData>& ducks, const float aspectRatio) {
    Vector2 maxDistance;

    for (auto it1 = ducks.begin(); it1 != ducks.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != ducks.end(); ++it2) {
            Vector2 difference = (it1->position - it2->position).abs();

            if (maxDistance.x() < difference.x())
                maxDistance.setX(difference.x());

            if (maxDistance.y() < difference.y())
                maxDistance.setY(difference.y());
        }
    }

    maxDistance.setX(maxDistance.x() + 30 * aspectRatio);
    maxDistance.setY(maxDistance.y() + 30);

    return maxDistance;
}

Vector2 Camera::centerOfDucks(const std::list<DuckData>& ducks) {
    Vector2 center = std::accumulate(
            ducks.begin(), ducks.end(), Vector2::ZERO,
            [](const Vector2& sum, const DuckData& duck) { return sum + duck.position; });

    if (not ducks.empty())
        center /= static_cast<float>(ducks.size());
    return center;
}

Rectangle& Camera::getViewRect() { return viewRect; }
