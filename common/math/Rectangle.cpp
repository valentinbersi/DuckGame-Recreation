#include "Rectangle.h"

#include <cmath>
#include <utility>

#include "Circle.h"
#include "Math.h"

Rectangle::Rectangle(Vector2 center, const float width, const float height):
        Shape2D(std::move(center)), _width(width), _height(height) {}

float Rectangle::width() const { return _width; }

float Rectangle::height() const { return _height; }

bool Rectangle::intersects(const Circle& circle) const { return circle.intersects(*this); }

bool Rectangle::intersects(const Rectangle& rectangle) const {
    const Vector2& rect1Center = this->center();
    const float rect1HalfWidth = this->width() / 2.0f;
    const float rect1HalfHeight = this->height() / 2.0f;

    const Vector2& rect2Center = rectangle.center();
    const float rect2HalfWidth = rectangle.width() / 2.0f;
    const float rect2HalfHeight = rectangle.height() / 2.0f;

    const bool overlapX =
            std::abs(rect1Center.x() - rect2Center.x()) <= rect1HalfWidth + rect2HalfWidth;
    const bool overlapY =
            std::abs(rect1Center.y() - rect2Center.y()) <= rect1HalfHeight + rect2HalfHeight;

    return overlapX and overlapY;
}
