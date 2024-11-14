#include "Circle.h"

#include <bitset>
#include <cmath>
#include <ranges>
#include <utility>

#include "Math.h"
#include "Rectangle.h"
#include "Segment.h"

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
        const Vector2 safeDisplacementProportion = Vector2(1, 1) - collisionNormal;
        const Vector2 safeDisplacement(displacement.x() * safeDisplacementProportion.x(),
                                       displacement.y() * safeDisplacementProportion.y());
        return {true, safeDisplacement, collisionNormal};
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
        const Vector2 safeDisplacementProportion = Vector2::ONE - collisionNormal;
        const Vector2 safeDisplacement(displacement.x() * safeDisplacementProportion.x(),
                                       displacement.y() * safeDisplacementProportion.y());

        return {true, safeDisplacement, collisionNormal};
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

IntersectionInfo Circle::intersects(const Rectangle& rectangle, const Vector2 displacement) const {
    const Segment circlePath(center(), center() + displacement);

    if (Circle(center() + displacement, _radius).intersects(rectangle))
        return {false};

    const std::array sides(rectangle.getSides());
    std::bitset<Rectangle::SidesAmount> collisionInSide;

    if (Math::isLessAprox(displacement.x(), 0))
        collisionInSide.set(Rectangle::West);
    else if (Math::isGreaterAprox(displacement.x(), 0))
        collisionInSide.set(Rectangle::East);

    if (Math::isLessAprox(displacement.y(), 0))
        collisionInSide.set(Rectangle::South);
    else if (Math::isGreaterAprox(displacement.y(), 0))
        collisionInSide.set(Rectangle::North);

    if (collisionInSide.test(Rectangle::North) and
        not(collisionInSide.test(Rectangle::East) or collisionInSide.test(Rectangle::West))) {

        if (const auto intersection = circlePath.intersects(sides[Rectangle::North]);
            intersection.has_value()) {
            const Vector2 safeHeight = Vector2::UP * _radius;

            Vector2 safePosition = intersection.value() + safeHeight - (displacement - safeHeight);
            return {true, intersection.value() + Vector2::UP * _radius, Vector2::UP};
        }
    }

    if (collisionInSide.test(Rectangle::South) and
        not(collisionInSide.test(Rectangle::East) or collisionInSide.test(Rectangle::West))) {
        if (const auto intersection = circlePath.intersects(sides[Rectangle::South]);
            intersection.has_value()) {
            const Vector2 safeHeight = Vector2::DOWN * _radius;

            Vector2 safePosition = intersection.value() + safeHeight - (displacement - safeHeight);
            return {true, intersection.value() + Vector2::DOWN * _radius, Vector2::DOWN};
        }
    }

    if (collisionInSide.test(Rectangle::West) and
        not(collisionInSide.test(Rectangle::North) or collisionInSide.test(Rectangle::South))) {
        if (const auto intersection = circlePath.intersects(sides[Rectangle::West]);
            intersection.has_value()) {
            const Vector2 safeHeight = Vector2::LEFT * _radius;

            Vector2 safePosition = intersection.value() + safeHeight - (displacement - safeHeight);
            return {true, intersection.value() + Vector2::LEFT * _radius, Vector2::LEFT};
        }
    }

    if (collisionInSide.test(Rectangle::East) and
        not(collisionInSide.test(Rectangle::North) or collisionInSide.test(Rectangle::South))) {
        if (const auto intersection = circlePath.intersects(sides[Rectangle::East]);
            intersection.has_value()) {
            const Vector2 safeHeight = Vector2::RIGHT * _radius;

            Vector2 safePosition = intersection.value() + safeHeight - (displacement - safeHeight);
            return {true, intersection.value() + Vector2::RIGHT * _radius, Vector2::RIGHT};
        }
    }

    // If this happens, we are cooked
    throw std::logic_error("Circle intersects rectangle but no collision detected");
}
