#include "Rectangle.h"

#include <cmath>
#include <utility>

#include "Circle.h"
#include "Math.h"
#include "Segment.h"

Rectangle::Rectangle(Vector2 center, const float width, const float height):
        Shape2D(std::move(center)), _width(width), _height(height) {}

float Rectangle::width() const { return _width; }

float Rectangle::height() const { return _height; }

std::array<Segment, Rectangle::SidesAmount> Rectangle::getSides() const {
    const Vector2& center = this->center();
    const float halfWidth = _width / 2.0f;
    const float halfHeight = _height / 2.0f;

    const Vector2 topLeft = center + Vector2(-halfWidth, halfHeight);
    const Vector2 topRight = center + Vector2(halfWidth, halfHeight);
    const Vector2 bottomLeft = center + Vector2(-halfWidth, -halfHeight);
    const Vector2 bottomRight = center + Vector2(halfWidth, -halfHeight);

    return {Segment(topLeft, topRight), Segment(topRight, bottomRight),
            Segment(bottomRight, bottomLeft), Segment(bottomLeft, topLeft)};
}

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
