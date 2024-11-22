#include "Camera.h"

#define DEFAULT_SCALE 2.5

Camera::Camera(int& windowWidth, int& windowHeight):
        windowWidth(windowWidth),
        windowHeight(windowHeight),
        backgroundWidth(0),
        backgroundHeight(0),
        x(0),
        y(0),
        scale(0),
        oldScale(0) {}

void Camera::update(std::list<std::unique_ptr<DuckData>>& ducks) {
    if (ducks.empty())
        return;

    calculateScale(ducks);
    //scale = 1;

    Vector2 center = centerOfDucks(ducks);
    float targetX = center.x();
    float targetY = center.y();

    x = targetX - windowWidth / 2;
    y = targetY - windowHeight / 2;

    /*if (targetX >= backgroundWidth - windowWidth / 2) {
        x = backgroundWidth - windowWidth;
    } else if (targetX > windowWidth / 2) {
        x = targetX - windowWidth / 2;
    } else {
        x = 0;
    }*/

    x = std::max(0.0f, std::min(x, static_cast<float>(backgroundWidth - windowWidth)));
    y = std::max(0.0f, std::min(y, static_cast<float>(backgroundHeight - windowHeight)));
}


/* esto mantiene los patos 'fijos con el background' pero rompe bastante otras cosas...
void Camera::adjustSpritePositions(std::list<std::unique_ptr<DuckData>>& ducks) {
    for (auto& duck : ducks) {
        duck->position.x((duck->position.x() - x) * scale);
        duck->position.y((duck->position.y() - y) * scale);
    }
}*/

void Camera::calculateScale(std::list<std::unique_ptr<DuckData>>& ducks) {

    // limites
    if (ducks.size() == 1) {
        scale = 4.0f * (windowWidth / 1040);  // Ajustar según el ancho de la ventana         (TEST,
        // SINO DEJAR SOLO 4.0F)
        auto& duck = ducks.front();
        x = duck->position.x() - windowWidth / 2;
        y = duck->position.y() - windowHeight / 2;
        return;
    }

    oldScale = scale;
    float maxDistance = calculateMaxDistance(ducks);

    // si la max distance es menor, se ajusta la escala
    // sino al reves
    // no mover la imgen y despues escalarla
    float desiredScale = std::clamp(100.0f / (maxDistance / 50.0f), 5.0f, 40.0f);
    desiredScale *= (windowWidth / 1040);  // Escalado relativo a la resolución       (TEST)

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
    size_t duckCount = ducks.size();
    Vector2 result;

    for (auto& duck: ducks) {
        result += duck->position;
    }

    if (duckCount > 0) {
        result /= static_cast<float>(duckCount);
    }

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

float Camera::getScale() const { return scale; }

int Camera::getBackgroundWidth() const { return backgroundWidth; }

int Camera::getBackgroundHeight() const { return backgroundHeight; }
