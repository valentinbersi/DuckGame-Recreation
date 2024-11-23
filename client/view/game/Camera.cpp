#include "Camera.h"

Camera::Camera(int& windowWidth, int& windowHeight):
        windowWidth(windowWidth),
        windowHeight(windowHeight),
        viewRect(Vector2::ZERO, {0, 0}),
        ducksArrived(false) {}

void Camera::update(std::list<DuckData>& ducks, const float deltaTime) {
    const float aspectRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
    const Vector2 center = centerOfDucks(ducks);
    const Vector2 maxDistance = calculateMaxDistance(ducks, aspectRatio);

    updateZoom(center, maxDistance, aspectRatio, deltaTime);

    if (not ducks.empty())
        ducksArrived = true;
}

void Camera::updateZoom(const Vector2& center, const Vector2& maxDistance, const float aspectRatio,
                        const float deltaTime) {
    const Vector2 rectDimension = maxDistance.x() > maxDistance.y() ?
                                          Vector2(maxDistance.x(), maxDistance.x() / aspectRatio) :
                                          Vector2(maxDistance.y() * aspectRatio, maxDistance.y());

    if (not ducksArrived) {
        viewRect.setSize(rectDimension);
        viewRect.setCenter(center);
        return;
    }

    viewRect.setSize(viewRect.size() + (rectDimension - viewRect.size()) * deltaTime);
    viewRect.setCenter(viewRect.center() + (center - viewRect.center()) * deltaTime);
}

Vector2 Camera::calculateMaxDistance(std::list<DuckData>& ducks, const float aspectRatio) {
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
    Vector2 center;
    for (const auto& duck: ducks) center += duck.position;
    if (not ducks.empty())
        center /= static_cast<float>(ducks.size());
    return center;
}

Rectangle& Camera::getViewRect() { return viewRect; }
