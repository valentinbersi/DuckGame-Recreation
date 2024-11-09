#include "Camera.h"

Camera::Camera(int& windowWidth, int& windowHeight):
        windowWidth(windowWidth), windowHeight(windowHeight),
        backgroundWidth(0), backgroundHeight(0),
        x(0),
        y(0), scale(0), oldScale(0) {}

void Camera::update(std::list<std::unique_ptr<DuckData>>& ducks) {
    if (ducks.empty()) return;

    Vector2 center = centerOfDucks(ducks);
    float targetX = center.x();
    float targetY = center.y();

    y = targetY - windowHeight / 2;

    if (targetX >= backgroundWidth - windowWidth / 2) {
        x = backgroundWidth - windowWidth;
    } else if (targetX > windowWidth / 2) {
        x = targetX - windowWidth / 2;
    } else {
        x = 0;
    }
    calculateScale(ducks);
}

void Camera::calculateScale(std::list<std::unique_ptr<DuckData>>& ducks) {
    if (ducks.size() == 1) {
        scale = 4.0f;
        auto& duck = ducks.front();
        x = duck->position.x() - windowWidth / 2;
        y = duck->position.y() - windowHeight / 2;
        return;
    }

    oldScale = scale;
    float maxDistance = calculateMaxDistance(ducks);
    float desiredScale = std::clamp(25.0f / (maxDistance / 70.0f), 0.7f, 5.0f);

    if (std::abs(desiredScale - scale) > 0.01f) {
        scale = desiredScale;
    }
}


float Camera::calculateMaxDistance(std::list<std::unique_ptr<DuckData>>& ducks) {
    float maxDistance = 0.0f;
    for (auto it1 = ducks.begin(); it1 != ducks.end(); ++it1) {
        for (auto it2 = std::next(it1); it2 != ducks.end(); ++it2) {
            float distance = (*it1)->position.distance((*it2)->position);
            if (distance > maxDistance) {
                maxDistance = distance;
            }
        }
    }
    return maxDistance;
}

Vector2 Camera::centerOfDucks(std::list<std::unique_ptr<DuckData>>& ducks) {
    float coordsX = 0.0f;
    float coordsY = 0.0f;
    size_t duckCount = ducks.size();

    for (auto& duck: ducks) {
        coordsX += duck->position.x();
        coordsY += duck->position.y();
    }

    if (duckCount > 0) {
        coordsX /= static_cast<float>(duckCount);
        coordsY /= static_cast<float>(duckCount);
    }

    Vector2 result(coordsX, coordsY);
    return result;
}

void Camera::loadBackgroundSize(SDL2pp::Texture& backgroundTexture) {
    backgroundWidth = backgroundTexture.GetWidth() * 2.5f;
    backgroundHeight = backgroundTexture.GetHeight() * 2.5f;
}

SDL_Rect Camera::getViewRect() {
    SDL_Rect viewRect;
    viewRect.x = static_cast<int>(x);
    viewRect.y = static_cast<int>(y);
    viewRect.w = windowWidth;
    viewRect.h = windowHeight;
    return viewRect;
}

float Camera::getScale() const {
    return scale;
}
