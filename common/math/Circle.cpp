#include "Circle.h"

#include <bitset>
#include <cmath>
#include <ranges>
#include <utility>

#include "Line.h"
#include "Math.h"
#include "Rectangle.h"

void Circle::calculateAxisPoints() {
    cachedAxisPoints = {center() + Vector2::UP * _radius, center() + Vector2::RIGHT * _radius,
                        center() + Vector2::DOWN * _radius, center() + Vector2::LEFT * _radius};
}

Circle::Circle(Vector2 center, const float radius): Shape2D(std::move(center)), _radius(radius) {}

Shape2D& Circle::setCenter(Vector2 center) {
    if (cachedAxisPoints.has_value())
        cachedAxisPoints.reset();

    return Shape2D::setCenter(std::move(center));
}

float Circle::radius() const { return _radius; }

Circle& Circle::radius(const float radius) {
    if (cachedAxisPoints.has_value())
        cachedAxisPoints.reset();

    _radius = radius;
    return *this;
}

bool Circle::contains(const Vector2& point) const {
    return center().distanceSquared(point) <= _radius * _radius;
}

bool Circle::intersects(const Circle& circle) const {
    return Math::isLessOrEqualAprox(center().distanceSquared(circle.center()),
                                    _radius * _radius + circle._radius * circle._radius);
}

std::optional<IntersectionInfo> Circle::intersects(const Circle& circle,
                                                   const Vector2 displacement) const {
    const Vector2 nextCenter = center() + displacement;

    if (Math::isEqualAprox(nextCenter.distance(circle.center()), _radius + circle._radius)) {
        const Vector2 collisionNormal = (center() - circle.center()).normalized();
        const Vector2 safeDisplacementProportion = Vector2(1, 1) - collisionNormal;
        const Vector2 safeDisplacement(displacement.x() * safeDisplacementProportion.x(),
                                       displacement.y() * safeDisplacementProportion.y());
        return {{center() + safeDisplacement, collisionNormal}};
    }

    if (Math::isLessOrEqualAprox(nextCenter.distanceSquared(circle.center()),
                                 _radius * _radius + circle._radius * circle._radius)) {

        const Vector2 centerDistance = circle.center() - center();

        // This variable names may seem terrible, but they are parameters for a quadratic
        // formula that need to be solved to calculate the circles new position
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

        return {{center() + safeDisplacement, collisionNormal}};
    }

    return std::nullopt;
}

bool Circle::intersects(const Rectangle& rectangle) const {
    const Vector2 circleCenter = center();

    const Vector2& rectCenter = rectangle.Shape2D::center();
    const float rectHalfWidth = rectangle.width() / 2.0f;
    const float rectHalfHeight = rectangle.height() / 2.0f;

    const Vector2 closestPoint(std::clamp(circleCenter.x(), rectCenter.x() - rectHalfWidth,
                                          rectCenter.x() + rectHalfWidth),
                               std::clamp(circleCenter.y(), rectCenter.y() - rectHalfHeight,
                                          rectCenter.y() + rectHalfHeight));

    return Math::isLessOrEqualAprox(circleCenter.distanceSquared(closestPoint), _radius * _radius);
}

std::optional<IntersectionInfo> Circle::intersects(const Rectangle& rectangle,
                                                   const Vector2 displacement) const {
    Circle nextCircle(center() + displacement, _radius);

    if (!nextCircle.intersects(rectangle))
        return std::nullopt;

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
        rectangle.contains(nextCircle.getAxisPoints()[South])) {
        const float collisionDistance = std::abs(rectangle.getAxisPoints()[Rectangle::North].y() -
                                                 nextCircle.getAxisPoints()[South].y());

        nextCircle.setCenter(center() + Vector2::UP * collisionDistance);
        return {{nextCircle.center(), Vector2::UP}};
    }

    if (collisionInSide.test(Rectangle::South) and
        rectangle.contains(nextCircle.getAxisPoints()[North])) {
        const float collisionDistance = std::abs(rectangle.getAxisPoints()[Rectangle::South].y() -
                                                 nextCircle.getAxisPoints()[North].y());

        nextCircle.setCenter(center() + Vector2::DOWN * collisionDistance);
        return {{nextCircle.center(), Vector2::DOWN}};
    }

    if (collisionInSide.test(Rectangle::East) and
        rectangle.contains(nextCircle.getAxisPoints()[West])) {
        const float collisionDistance = std::abs(rectangle.getAxisPoints()[Rectangle::East].y() -
                                                 nextCircle.getAxisPoints()[West].y());

        nextCircle.setCenter(center() + Vector2::RIGHT * collisionDistance);
        return {{nextCircle.center(), Vector2::RIGHT}};
    }

    if (collisionInSide.test(Rectangle::West) and
        rectangle.contains(nextCircle.getAxisPoints()[East])) {
        const float collisionDistance = std::abs(rectangle.getAxisPoints()[Rectangle::West].y() -
                                                 nextCircle.getAxisPoints()[East].y());

        nextCircle.setCenter(center() + Vector2::LEFT * collisionDistance);
        return {{nextCircle.center(), Vector2::LEFT}};
    }

    if (collisionInSide.test(North) and collisionInSide.test(East) and
        nextCircle.contains(rectangle.getVertices()[Rectangle::NorthEast])) {
        if (Math::isGreaterAprox(std::abs(displacement.y()), std::abs(displacement.x()))) {
            const float collisionDistance =
                    std::abs(rectangle.getAxisPoints()[Rectangle::North].y() -
                             nextCircle.getAxisPoints()[South].y());

            nextCircle.setCenter(center() + Vector2::UP * collisionDistance);
            return {{nextCircle.center(), Vector2::UP}};
        }

        const float collisionDistance = std::abs(rectangle.getAxisPoints()[Rectangle::East].y() -
                                                 nextCircle.getAxisPoints()[West].y());

        nextCircle.setCenter(center() + Vector2::RIGHT * collisionDistance);
        return {{nextCircle.center(), Vector2::RIGHT}};
    }

    if (collisionInSide.test(North) and collisionInSide.test(West) and
        nextCircle.contains(rectangle.getVertices()[Rectangle::NorthWest])) {
        if (Math::isGreaterAprox(std::abs(displacement.y()), std::abs(displacement.x()))) {
            const float collisionDistance =
                    std::abs(rectangle.getAxisPoints()[Rectangle::North].y() -
                             nextCircle.getAxisPoints()[South].y());

            nextCircle.setCenter(center() + Vector2::UP * collisionDistance);
            return {{nextCircle.center(), Vector2::UP}};
        }
        const float collisionDistance = std::abs(rectangle.getAxisPoints()[Rectangle::West].y() -
                                                 nextCircle.getAxisPoints()[East].y());

        nextCircle.setCenter(center() + Vector2::LEFT * collisionDistance);
        return {{nextCircle.center(), Vector2::LEFT}};
    }

    if (collisionInSide.test(South) and collisionInSide.test(East) and
        nextCircle.contains(rectangle.getVertices()[Rectangle::SouthEast])) {
        if (Math::isGreaterAprox(std::abs(displacement.y()), std::abs(displacement.x()))) {
            const float collisionDistance =
                    std::abs(rectangle.getAxisPoints()[Rectangle::South].y() -
                             nextCircle.getAxisPoints()[North].y());

            nextCircle.setCenter(center() + Vector2::DOWN * collisionDistance);
            return {{nextCircle.center(), Vector2::DOWN}};
        }
        const float collisionDistance = std::abs(rectangle.getAxisPoints()[Rectangle::East].y() -
                                                 nextCircle.getAxisPoints()[West].y());

        nextCircle.setCenter(center() + Vector2::RIGHT * collisionDistance);
        return {{nextCircle.center(), Vector2::RIGHT}};
    }


    if (Math::isGreaterAprox(std::abs(displacement.y()), std::abs(displacement.x()))) {
        const float collisionDistance = std::abs(rectangle.getAxisPoints()[Rectangle::South].y() -
                                                 nextCircle.getAxisPoints()[North].y());

        nextCircle.setCenter(center() + Vector2::DOWN * collisionDistance);
        return {{nextCircle.center(), Vector2::DOWN}};
    }
    const float collisionDistance = std::abs(rectangle.getAxisPoints()[Rectangle::West].y() -
                                             nextCircle.getAxisPoints()[East].y());

    nextCircle.setCenter(center() + Vector2::LEFT * collisionDistance);
    return {{nextCircle.center(), Vector2::LEFT}};
}

Circle::AxisPoints Circle::getAxisPoints() {
    if (!cachedAxisPoints.has_value())
        calculateAxisPoints();

    return cachedAxisPoints.value();
}
