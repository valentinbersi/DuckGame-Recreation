#include "Rectangle.h"

#include <cmath>
#include <utility>

#include <bits/ranges_algo.h>

#include "Capsule.h"
#include "Circle.h"
#include "Math.h"

bool Rectangle::overlapOnAxis(const std::array<Vector2, VertexAmount>& rect2Vertices,
                              const Vector2& axis) const {
    auto project = [](const std::array<Vector2, 4>& rect, const Vector2& axis) {
        float min = rect[0].dot(axis);
        float max = min;
        for (const auto& corner: rect) {
            const float projection = corner.dot(axis);
            if (projection < min)
                min = projection;
            if (projection > max)
                max = projection;
        }
        return std::make_pair(min, max);
    };

    auto [min1, max1] = project(this->vertices(), axis);
    auto [min2, max2] = project(rect2Vertices, axis);

    return max1 >= min2 && max2 >= min1;
}

std::array<Vector2, Rectangle::VertexAmount> Rectangle::vertices() const {
    std::array<Vector2, VertexAmount> corners;
    const float cosAngle = std::cos(rotation());
    const float sinAngle = std::sin(rotation());

    const Vector2 halfExtents = {_width / 2, _height / 2};

    corners[Vertex::TopLeft] =
            this->center() + Vector2{cosAngle * halfExtents.x() - sinAngle * halfExtents.y(),
                                     sinAngle * halfExtents.x() + cosAngle * halfExtents.y()};
    corners[Vertex::TopRight] =
            this->center() + Vector2{cosAngle * -halfExtents.x() - sinAngle * halfExtents.y(),
                                     sinAngle * -halfExtents.x() + cosAngle * halfExtents.y()};
    corners[Vertex::BottomLeft] =
            this->center() + Vector2{cosAngle * -halfExtents.x() - sinAngle * -halfExtents.y(),
                                     sinAngle * -halfExtents.x() + cosAngle * -halfExtents.y()};
    corners[Vertex::BottomRight] =
            this->center() + Vector2{cosAngle * halfExtents.x() - sinAngle * -halfExtents.y(),
                                     sinAngle * halfExtents.x() + cosAngle * -halfExtents.y()};

    return corners;
}

Rectangle::Vertex::Vertex(const Vertex& other) = default;

Rectangle::Vertex& Rectangle::Vertex::operator=(const Vertex& other) = default;

Rectangle::Vertex::Vertex(Vertex&& other) noexcept: value(other.value) { other.value = Invalid; }

Rectangle::Vertex& Rectangle::Vertex::operator=(Vertex&& other) noexcept {
    if (this == &other)
        return *this;

    value = other.value;
    other.value = Invalid;
    return *this;
}

Rectangle::Vertex::Vertex(const Value value): value(value) {}

bool Rectangle::Vertex::operator==(const Vertex other) const { return value == other.value; }

bool Rectangle::Vertex::operator!=(const Vertex other) const { return value != other.value; }

Rectangle::Vertex::operator Value() const { return value; }

Rectangle::Vertex::operator bool() const { return value != Invalid; }

bool Rectangle::Vertex::isValidValue(const u8 value) { return value < Invalid; }

Rectangle::Rectangle(const Rectangle& other) = default;

Rectangle& Rectangle::operator=(const Rectangle& other) = default;

Rectangle::Rectangle(Rectangle&& other) noexcept:
        Shape2D(std::move(other)), _width(other._width), _height(other._height) {
    other._width = 0;
    other._height = 0;
}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    if (this == &other)
        return *this;

    Shape2D::operator=(std::move(other));
    _width = other._width;
    _height = other._height;
    other._width = 0;
    other._height = 0;
    return *this;
};

Rectangle::Rectangle(Vector2 center, const float rotation, const float width, const float height):
        Shape2D(std::move(center), rotation), _width(width), _height(height) {}

float Rectangle::width() const { return _width; }

float Rectangle::height() const { return _height; }

bool Rectangle::intersects(const Circle& circle) const {
    // Get the bounds of the rectangle
    const float rectHalfWidth = _width / 2.0f;
    const float rectHalfHeight = _height / 2.0f;

    // Calculate the sine and cosine of the rotation angle
    const float sinAngle = std::sin(-rotation());
    const float cosAngle = std::cos(-rotation());

    // Rotate the circle's center in the opposite direction of the rectangle's rotation
    const Vector2 rotatedCircleCenter(
            cosAngle * (circle.center().x() - center().x()) -
                    sinAngle * (circle.center().y() - center().y()) + center().x(),
            sinAngle * (circle.center().x() - center().x()) +
                    cosAngle * (circle.center().y() - center().y()) + center().y());

    // Find the closest point to the rotated circle within the axis-aligned rectangle
    const Vector2 closestPoint(std::clamp(rotatedCircleCenter.x(), center().x() - rectHalfWidth,
                                          center().x() + rectHalfWidth),
                               std::clamp(rotatedCircleCenter.y(), center().y() - rectHalfHeight,
                                          center().y() + rectHalfHeight));

    // Calculate the distance between the rotated circle's center and this closest point within the
    // rectangle
    return Math::isLessOrEqualAprox(rotatedCircleCenter.distanceSquared(closestPoint),
                                    circle.radius() * circle.radius());
}

bool Rectangle::intersects(const Rectangle& rectangle) const {
    const std::array thisVertices(vertices());
    const std::array rectVertices(rectangle.vertices());

    const std::array axes = {
            Vector2{thisVertices[Vertex::TopRight].x() - thisVertices[Vertex::TopLeft].x(),
                    thisVertices[Vertex::TopRight].y() - thisVertices[Vertex::TopLeft].y()},
            Vector2{thisVertices[Vertex::BottomRight].x() - thisVertices[Vertex::TopLeft].x(),
                    thisVertices[Vertex::BottomRight].y() - thisVertices[Vertex::TopLeft].y()},
            Vector2{rectVertices[Vertex::TopRight].x() - rectVertices[Vertex::TopLeft].x(),
                    rectVertices[Vertex::TopRight].y() - rectVertices[Vertex::TopLeft].y()},
            Vector2{rectVertices[Vertex::BottomRight].x() - rectVertices[Vertex::TopLeft].x(),
                    rectVertices[Vertex::BottomRight].y() - rectVertices[Vertex::TopLeft].y()}};

    return std::ranges::all_of(axes, [this, &rectVertices](const Vector2& axis) {
        return overlapOnAxis(rectVertices, axis);
    });
}

bool Rectangle::intersects(const Capsule& capsule) const { return capsule.intersects(*this); }

std::unique_ptr<Shape2D> Rectangle::clone() const { return std::make_unique<Rectangle>(*this); }
