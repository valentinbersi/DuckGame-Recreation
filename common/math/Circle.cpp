#include "Circle.h"

#include <utility>

#include "Math.h"
#include "Rectangle.h"

Circle::Circle(Vector2 center, const float radius): Shape2D(std::move(center)), _radius(radius) {}

float Circle::radius() const { return _radius; }

Circle& Circle::radius(const float radius) {
    _radius = radius;
    return *this;
}

bool Circle::intersects(const Circle& circle) const {
    return Math::isLessOrEqualAprox(center().distanceSquared(circle.center()),
                                    _radius * _radius + circle._radius * circle._radius);
}

bool Circle::intersects(const Rectangle& rectangle) const {
    const Vector2 circleCenter = center();

    const Vector2& rectCenter = rectangle.center();
    const float rectHalfWidth = rectangle.width() / 2.0f;
    const float rectHalfHeight = rectangle.height() / 2.0f;

    const Vector2 closestPoint(std::clamp(circleCenter.x(), rectCenter.x() - rectHalfWidth,
                                          rectCenter.x() + rectHalfWidth),
                               std::clamp(circleCenter.y(), rectCenter.y() - rectHalfHeight,
                                          rectCenter.y() + rectHalfHeight));

    return Math::isLessOrEqualAprox(circleCenter.distanceSquared(closestPoint), _radius * _radius);
}
