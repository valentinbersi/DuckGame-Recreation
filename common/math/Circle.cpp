#include "Circle.h"

#include <cmath>
#include <utility>

#include "Math.h"
#include "Rectangle.h"

bool Circle::touches(const Circle& circle) const {
    return Math::isEqualAprox(center().distance(circle.center()), _radius + circle._radius);
}

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

IntersectionInfo Circle::intersects(const Circle& circle, const Vector2 displacement) const {
    const Vector2 nextCenter = center() + displacement;

    if (Math::isEqualAprox(nextCenter.distance(circle.center()), _radius + circle._radius)) {
        const Vector2 collisionNormal = (center() - circle.center()).normalized();
        const Vector2 touchingPoint = center() + collisionNormal * _radius;
        return {true, touchingPoint, collisionNormal};
    }

    if (Math::isLessOrEqualAprox(nextCenter.distanceSquared(circle.center()),
                                 _radius * _radius + circle._radius * circle._radius)) {

        const Vector2 centerDistance = circle.center() - center();

        // This variable names may seem terrible, but they are parameters for a quadratic formula
        // that need to be solved to calculate the circles new position
        const float b =
                -2 *
                (centerDistance.x() * displacement.x() + centerDistance.y() * displacement.y()) /
                std::sqrt(displacement.dot(displacement));

        const float c = centerDistance.lengthSquared() -
                        (_radius + circle._radius) * (_radius + circle._radius);

        const float realDisplacementLenght = std::ranges::min(Math::solveQuadratic(1, b, c));
        const Vector2 realDisplacement = displacement.normalized() * realDisplacementLenght;
        const Vector2 newPosition = center() + realDisplacement;
        const Vector2 collisionNormal = (newPosition - circle.center()).normalized();
        return {true, newPosition, collisionNormal};
    }

    return {false};
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
