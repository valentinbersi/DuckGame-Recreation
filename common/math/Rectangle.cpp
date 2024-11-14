#include "Rectangle.h"

#include <bitset>
#include <cmath>
#include <utility>

#include "Circle.h"
#include "Line.h"
#include "Math.h"
#include "Segment.h"

void Rectangle::calculateVertices() {
    const Vector2& center = this->center();
    const float halfWidth = _width / 2.0f;
    const float halfHeight = _height / 2.0f;

    const Vector2 topLeft = center + Vector2(-halfWidth, halfHeight);
    const Vector2 topRight = center + Vector2(halfWidth, halfHeight);
    const Vector2 bottomLeft = center + Vector2(-halfWidth, -halfHeight);
    const Vector2 bottomRight = center + Vector2(halfWidth, -halfHeight);

    cachedVertices = {topLeft, topRight, bottomRight, bottomLeft};
}

void Rectangle::calculateSides() {
    calculateVertices();
    cachedSides = {Segment(getVertices()[NorthWest], getVertices()[NorthEast]),
                   Segment(getVertices()[NorthEast], getVertices()[SouthEast]),
                   Segment(getVertices()[SouthEast], getVertices()[SouthWest]),
                   Segment(getVertices()[SouthWest], getVertices()[NorthWest])};
}

void Rectangle::calculateAxisPoints() {
    const float midWidth = _width / 2.0f;
    const float midHeight = _height / 2.0f;

    cachedAxisPoints = {center() + Vector2::UP * midHeight, center() + Vector2::RIGHT * midWidth,
                        center() + Vector2::DOWN * midHeight, center() + Vector2::LEFT * midWidth};
}

Shape2D& Rectangle::setCenter(Vector2 center) {
    if (this->center() != center) {
        cachedSides.reset();
        cachedVertices.reset();
    }

    return Shape2D::setCenter(std::move(center));
}

Rectangle::Rectangle(Vector2 center, const float width, const float height):
        Shape2D(std::move(center)),
        _width(width),
        _height(height),
        cachedSides(std::nullopt),
        cachedVertices(std::nullopt) {}

float Rectangle::width() const { return _width; }

float Rectangle::height() const { return _height; }

Rectangle::Region Rectangle::regionOfPoint(const Vector2& point) const {
    const auto vertices = getVertices();

    if (Math::isLessAprox(vertices[NorthWest].y(), point.y())) {       // North situation
        if (Math::isGreaterAprox(vertices[NorthWest].x(), point.x()))  // NorthWest situation
            return Region::NorthWest;

        if (Math::isLessAprox(vertices[NorthEast].x(), point.x()))  // NorthEast situation
            return Region::NorthEast;

        return Region::North;
    }

    if (Math::isGreaterAprox(vertices[NorthWest].y(), point.y())) {    // South situation
        if (Math::isGreaterAprox(vertices[NorthWest].x(), point.x()))  // SouthWest situation
            return Region::SouthWest;

        if (Math::isLessAprox(vertices[NorthEast].x(), point.x()))  // SouthEast situation
            return Region::SouthEast;

        return Region::South;
    }

    if (Math::isGreaterAprox(vertices[NorthWest].x(), point.x()))  // West situation
        return Region::West;

    return Region::East;
}

const Rectangle::Sides& Rectangle::getSides() const {
    if (not cachedSides.has_value())
        const_cast<Rectangle*>(this)->calculateSides();

    return cachedSides.value();
}

std::array<Vector2, Rectangle::VertexAmount> Rectangle::getVertices() const {
    if (not cachedVertices.has_value())
        const_cast<Rectangle*>(this)->calculateVertices();

    return cachedVertices.value();
}

Rectangle::AxisPoints Rectangle::getAxisPoints() const {
    if (not cachedAxisPoints.has_value())
        const_cast<Rectangle*>(this)->calculateAxisPoints();

    return cachedAxisPoints.value();
}

bool Rectangle::contains(const Vector2& point) const {
    const auto vertices = getVertices();
    const float minX = std::min(vertices[NorthWest].x(), vertices[SouthWest].x());
    const float maxX = std::max(vertices[NorthEast].x(), vertices[SouthEast].x());
    const float minY = std::min(vertices[SouthWest].y(), vertices[SouthEast].y());
    const float maxY = std::max(vertices[NorthWest].y(), vertices[NorthEast].y());

    return point.x() >= minX && point.x() <= maxX && point.y() >= minY && point.y() <= maxY;
}

bool Rectangle::intersects(const Circle& circle) const { return circle.intersects(*this); }

std::optional<IntersectionInfo> Rectangle::intersects(
        [[maybe_unused]] const Circle& circle, [[maybe_unused]] const Vector2 displacement) const {
    std::optional intersectionInfo(circle.intersects(*this, -displacement));

    if (not intersectionInfo.has_value())
        return std::nullopt;

    const Vector2 rectangleReadDisplacement = circle.center() - intersectionInfo->nextPosition;
    intersectionInfo->nextPosition = center() + rectangleReadDisplacement;
    return intersectionInfo;
}

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

std::optional<IntersectionInfo> Rectangle::intersects([[maybe_unused]] const Rectangle& rectangle,
                                                      [[maybe_unused]] Vector2 displacement) const {
    Rectangle nextRectangle(center() + displacement, _width, _height);

    if (!nextRectangle.intersects(rectangle))
        return std::nullopt;

    const Line velocityLine(center() + displacement, center());
    std::bitset<SidesAmount> collisionInSide;

    if (Math::isLessAprox(displacement.x(), 0))
        collisionInSide.set(West);
    else if (Math::isGreaterAprox(displacement.x(), 0))
        collisionInSide.set(East);

    if (Math::isLessAprox(displacement.y(), 0))
        collisionInSide.set(South);
    else if (Math::isGreaterAprox(displacement.y(), 0))
        collisionInSide.set(North);

    if (collisionInSide.test(North) and rectangle.contains(nextRectangle.getAxisPoints()[South])) {
        const float collisionDistance = std::abs(rectangle.getAxisPoints()[North].y() -
                                                 nextRectangle.getAxisPoints()[South].y());

        nextRectangle.setCenter(center() + Vector2::UP * collisionDistance);
        return {{nextRectangle.center(), Vector2::UP}};
    }

    if (collisionInSide.test(South) and rectangle.contains(nextRectangle.getAxisPoints()[North])) {
        const float collisionDistance = std::abs(rectangle.getAxisPoints()[South].y() -
                                                 nextRectangle.getAxisPoints()[North].y());

        nextRectangle.setCenter(center() + Vector2::DOWN * collisionDistance);
        return {{nextRectangle.center(), Vector2::DOWN}};
    }

    if (collisionInSide.test(East) and rectangle.contains(nextRectangle.getAxisPoints()[West])) {
        const float collisionDistance = std::abs(rectangle.getAxisPoints()[East].y() -
                                                 nextRectangle.getAxisPoints()[West].y());

        nextRectangle.setCenter(center() + Vector2::RIGHT * collisionDistance);
        return {{nextRectangle.center(), Vector2::RIGHT}};
    }

    if (collisionInSide.test(West) and rectangle.contains(nextRectangle.getAxisPoints()[East])) {
        const float collisionDistance = std::abs(rectangle.getAxisPoints()[West].y() -
                                                 nextRectangle.getAxisPoints()[East].y());

        nextRectangle.setCenter(center() + Vector2::LEFT * collisionDistance);
        return {{nextRectangle.center(), Vector2::LEFT}};
    }

    if (collisionInSide.test(North) and collisionInSide.test(East) and
        nextRectangle.contains(rectangle.getVertices()[NorthEast])) {
        if (Math::isGreaterAprox(std::abs(displacement.y()), std::abs(displacement.x()))) {
            const float collisionDistance = std::abs(rectangle.getAxisPoints()[North].y() -
                                                     nextRectangle.getAxisPoints()[South].y());

            nextRectangle.setCenter(center() + Vector2::UP * collisionDistance);
            return {{nextRectangle.center(), Vector2::UP}};
        }

        const float collisionDistance = std::abs(rectangle.getAxisPoints()[East].y() -
                                                 nextRectangle.getAxisPoints()[West].y());

        nextRectangle.setCenter(center() + Vector2::RIGHT * collisionDistance);
        return {{nextRectangle.center(), Vector2::RIGHT}};
    }

    if (collisionInSide.test(North) and collisionInSide.test(West) and
        nextRectangle.contains(rectangle.getVertices()[NorthWest])) {
        if (Math::isGreaterAprox(std::abs(displacement.y()), std::abs(displacement.x()))) {
            const float collisionDistance = std::abs(rectangle.getAxisPoints()[North].y() -
                                                     nextRectangle.getAxisPoints()[South].y());

            nextRectangle.setCenter(center() + Vector2::UP * collisionDistance);
            return {{nextRectangle.center(), Vector2::UP}};
        }
        const float collisionDistance = std::abs(rectangle.getAxisPoints()[West].y() -
                                                 nextRectangle.getAxisPoints()[East].y());

        nextRectangle.setCenter(center() + Vector2::LEFT * collisionDistance);
        return {{nextRectangle.center(), Vector2::LEFT}};
    }

    if (collisionInSide.test(South) and collisionInSide.test(East) and
        nextRectangle.contains(rectangle.getVertices()[SouthEast])) {
        if (Math::isGreaterAprox(std::abs(displacement.y()), std::abs(displacement.x()))) {
            const float collisionDistance = std::abs(rectangle.getAxisPoints()[South].y() -
                                                     nextRectangle.getAxisPoints()[North].y());

            nextRectangle.setCenter(center() + Vector2::DOWN * collisionDistance);
            return {{nextRectangle.center(), Vector2::DOWN}};
        }
        const float collisionDistance = std::abs(rectangle.getAxisPoints()[East].y() -
                                                 nextRectangle.getAxisPoints()[West].y());

        nextRectangle.setCenter(center() + Vector2::RIGHT * collisionDistance);
        return {{nextRectangle.center(), Vector2::RIGHT}};
    }


    if (Math::isGreaterAprox(std::abs(displacement.y()), std::abs(displacement.x()))) {
        const float collisionDistance = std::abs(rectangle.getAxisPoints()[South].y() -
                                                 nextRectangle.getAxisPoints()[North].y());

        nextRectangle.setCenter(center() + Vector2::DOWN * collisionDistance);
        return {{nextRectangle.center(), Vector2::DOWN}};
    }
    const float collisionDistance =
            std::abs(rectangle.getAxisPoints()[West].y() - nextRectangle.getAxisPoints()[East].y());

    nextRectangle.setCenter(center() + Vector2::LEFT * collisionDistance);
    return {{nextRectangle.center(), Vector2::LEFT}};
}
