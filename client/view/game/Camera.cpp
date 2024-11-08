#include "Camera.h"

Camera::Camera(int& windowWidth, int& windowHeight):
        windowWidth(windowWidth), windowHeight(windowHeight),
        backgroundWidth(0), backgroundHeight(0),
        x(0),
        y(0) {};

void Camera::update(float targetX, float targetY) {
    y = targetY - windowHeight / 2;

    if (targetX >= backgroundWidth - windowWidth / 2) {
        x = backgroundWidth - windowWidth;
    } else if (targetX > windowWidth / 2) {
        x = targetX - windowWidth / 2;
    } else {
        x = 0;
    }
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
