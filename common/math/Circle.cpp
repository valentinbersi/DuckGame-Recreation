#include "Circle.h"

#include <utility>

#include "Capsule.h"
#include "Math.h"
#include "Rectangle.h"

Circle::Circle(const Circle& other) = default;

Circle& Circle::operator=(const Circle& other) = default;

Circle::Circle(Circle&& other) noexcept: Shape2D(std::move(other)), _radius(other._radius) {}

Circle& Circle::operator=(Circle&& other) noexcept {
    Shape2D::operator=(std::move(other));
    _radius = other._radius;
    return *this;
}

Circle::Circle(Vector2 center, const float radius):
        Shape2D(std::move(center), 0), _radius(radius) {}

float Circle::radius() const { return _radius; }

Circle& Circle::radius(const float radius) {
    _radius = radius;
    return *this;
}

bool Circle::intersects(const Circle& circle) const {
    return Math::isLessOrEqualAprox(center().distance(circle.center()), _radius + circle._radius);
}

bool Circle::intersects(const Rectangle& rectangle) const {
    const Vector2 circleCenter = center();

    // Get the bounds of the rectangle
    const Vector2& rectCenter = rectangle.center();
    const float rectHalfWidth = rectangle.width() / 2.0f;
    const float rectHalfHeight = rectangle.height() / 2.0f;

    // Calculate the sine and cosine of the rotation angle
    const float sinAngle = std::sin(-rotation());
    const float cosAngle = std::cos(-rotation());

    // Rotate the circle's center in the opposite direction of the rectangle's rotation
    const Vector2 rotatedCircleCenter(
            cosAngle * (circleCenter.x() - rectCenter.x()) -
                    sinAngle * (circleCenter.y() - rectCenter.y()) + rectCenter.x(),
            sinAngle * (circleCenter.x() - rectCenter.x()) +
                    cosAngle * (circleCenter.y() - rectCenter.y()) + rectCenter.y());

    // Find the closest point to the rotated circle within the axis-aligned rectangle
    const Vector2 closestPoint(std::clamp(rotatedCircleCenter.x(), rectCenter.x() - rectHalfWidth,
                                          rectCenter.x() + rectHalfWidth),
                               std::clamp(rotatedCircleCenter.y(), rectCenter.y() - rectHalfHeight,
                                          rectCenter.y() + rectHalfHeight));

    // Calculate the distance between the rotated circle's center and this closest point within the
    // rectangle
    return Math::isLessOrEqualAprox(rotatedCircleCenter.distanceSquared(closestPoint),
                                    _radius * _radius);
}

bool Circle::intersects(const Capsule& capsule) const { return capsule.intersects(*this); }

std::unique_ptr<Shape2D> Circle::clone() const { return std::make_unique<Circle>(*this); }
