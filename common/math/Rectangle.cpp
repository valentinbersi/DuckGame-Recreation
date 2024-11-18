#include "Rectangle.h"

#include <bitset>
#include <cmath>
#include <utility>

#include "Math.h"
#include "Segment.h"

void Rectangle::invalidateCachedValues() {
    cachedSides.reset();
    cachedVertices.reset();
    cachedAxisPoints.reset();
}

void Rectangle::calculateVertices() {
    const Vector2& center = this->center();
    const float halfWidth = _width / 2.0f;
    const float halfHeight = _height / 2.0f;

    const Vector2 topLeft = center + Vector2(-halfWidth, -halfHeight);
    const Vector2 topRight = center + Vector2(halfWidth, -halfHeight);
    const Vector2 bottomLeft = center + Vector2(-halfWidth, halfHeight);
    const Vector2 bottomRight = center + Vector2(halfWidth, halfHeight);

    cachedVertices = {topLeft, topRight, bottomRight, bottomLeft};
}

void Rectangle::calculateSides() {
    calculateVertices();
    cachedSides = {Segment(vertices()[NorthWest], vertices()[NorthEast]),
                   Segment(vertices()[NorthEast], vertices()[SouthEast]),
                   Segment(vertices()[SouthEast], vertices()[SouthWest]),
                   Segment(vertices()[SouthWest], vertices()[NorthWest])};
}

void Rectangle::calculateAxisPoints() {
    const float midWidth = _width / 2.0f;
    const float midHeight = _height / 2.0f;

    cachedAxisPoints = {center() + Vector2::UP * midHeight, center() + Vector2::RIGHT * midWidth,
                        center() + Vector2::DOWN * midHeight, center() + Vector2::LEFT * midWidth};
}

std::optional<Vector2> Rectangle::calculateNorthIntersection(const Rectangle& rectangle,
                                                             const Rectangle& nextRectangle) const {

    const float collisionDistance =
            std::abs(rectangle.axisPoints()[North].y() - nextRectangle.axisPoints()[South].y());

    return nextRectangle._center + Vector2::UP * collisionDistance - _center;
}

std::optional<Vector2> Rectangle::calculateSouthIntersection(const Rectangle& rectangle,
                                                             const Rectangle& nextRectangle) const {
    const float collisionDistance =
            std::abs(rectangle.axisPoints()[South].y() - nextRectangle.axisPoints()[North].y());

    return {nextRectangle._center + Vector2::DOWN * collisionDistance - _center};
}

std::optional<Vector2> Rectangle::calculateEastIntersection(const Rectangle& rectangle,
                                                            const Rectangle& nextRectangle) const {
    const float collisionDistance =
            std::abs(rectangle.axisPoints()[East].y() - nextRectangle.axisPoints()[West].y());

    return {nextRectangle._center + Vector2::RIGHT * collisionDistance - _center};
}

std::optional<Vector2> Rectangle::calculateWestIntersection(const Rectangle& rectangle,
                                                            const Rectangle& nextRectangle) const {
    const float collisionDistance =
            std::abs(rectangle.axisPoints()[West].y() - nextRectangle.axisPoints()[East].y());

    return {nextRectangle._center + Vector2::LEFT * collisionDistance - _center};
}

std::optional<Vector2> Rectangle::calculateNorthEastIntersection(
        const Rectangle& rectangle, const Vector2& displacement,
        const Rectangle& nextRectangle) const {

    const float yDistance =
            std::abs(rectangle.sides()[North].intersects(sides()[East]).value().y() -
                     vertices()[SouthEast].y());

    const float xDistance =
            std::abs(rectangle.sides()[West].intersects(sides()[South]).value().x() -
                     vertices()[SouthEast].x());

    if (not Math::isEqualAprox(yDistance, xDistance)) {
        if (Math::isGreaterAprox(yDistance, xDistance))
            return calculateNorthIntersection(rectangle, nextRectangle);

        return calculateWestIntersection(rectangle, nextRectangle);
    }

    if (Math::isEqualAprox(std::abs(displacement.y()), std::abs(displacement.x())))
        return {rectangle.vertices()[NorthEast] + Vector2(_width / 2, -_height / 2) - _center};

    if (Math::isGreaterAprox(std::abs(displacement.y()), std::abs(displacement.x())))
        return calculateNorthIntersection(rectangle, nextRectangle);

    return calculateWestIntersection(rectangle, nextRectangle);
}

std::optional<Vector2> Rectangle::calculateNorthWestIntersection(
        const Rectangle& rectangle, const Vector2& displacement,
        const Rectangle& nextRectangle) const {

    const float yDistance =
            std::abs(rectangle.sides()[North].intersects(sides()[East]).value().y() -
                     vertices()[SouthEast].y());

    const float xDistance =
            std::abs(rectangle.sides()[West].intersects(sides()[South]).value().x() -
                     vertices()[SouthEast].x());

    if (not Math::isEqualAprox(yDistance, xDistance)) {
        if (Math::isGreaterAprox(yDistance, xDistance))
            return calculateNorthIntersection(rectangle, nextRectangle);

        return calculateWestIntersection(rectangle, nextRectangle);
    }

    if (Math::isEqualAprox(std::abs(displacement.y()), std::abs(displacement.x())))
        return {rectangle.vertices()[NorthWest] + Vector2(-_width / 2, -_height / 2) - _center};

    if (Math::isGreaterAprox(std::abs(displacement.y()), std::abs(displacement.x())))
        return calculateNorthIntersection(rectangle, nextRectangle);

    return calculateWestIntersection(rectangle, nextRectangle);
}

std::optional<Vector2> Rectangle::calculateSouthEastIntersection(
        const Rectangle& rectangle, const Vector2& displacement,
        const Rectangle& nextRectangle) const {

    const float yDistance =
            std::abs(rectangle.sides()[South].intersects(sides()[West]).value().y() -
                     vertices()[NorthWest].y());

    const float xDistance =
            std::abs(rectangle.sides()[East].intersects(sides()[North]).value().x() -
                     vertices()[NorthWest].x());

    if (not Math::isEqualAprox(yDistance, xDistance)) {
        if (Math::isGreaterAprox(yDistance, xDistance))
            return calculateSouthIntersection(rectangle, nextRectangle);

        return calculateEastIntersection(rectangle, nextRectangle);
    }

    if (Math::isEqualAprox(std::abs(displacement.y()), std::abs(displacement.x())))
        return {rectangle.vertices()[SouthEast] + Vector2(_width, _height) - _center};

    if (Math::isGreaterAprox(std::abs(displacement.y()), std::abs(displacement.x())))
        return calculateSouthIntersection(rectangle, nextRectangle);

    return calculateEastIntersection(rectangle, nextRectangle);
}

std::optional<Vector2> Rectangle::calculateSouthWestIntersection(
        const Rectangle& rectangle, const Vector2& displacement,
        const Rectangle& nextRectangle) const {

    const float yDistance =
            std::abs(rectangle.sides()[South].intersects(sides()[East]).value().y() -
                     vertices()[NorthEast].y());

    const float xDistance =
            std::abs(rectangle.sides()[West].intersects(sides()[North]).value().x() -
                     vertices()[NorthEast].x());

    if (not Math::isEqualAprox(yDistance, xDistance)) {
        if (Math::isGreaterAprox(yDistance, xDistance))
            return calculateSouthIntersection(rectangle, nextRectangle);

        return calculateWestIntersection(rectangle, nextRectangle);
    }

    if (Math::isEqualAprox(std::abs(displacement.y()), std::abs(displacement.x())))
        return {rectangle.vertices()[SouthWest] - Vector2(-_width / 2, _height / 2) - _center};


    if (Math::isGreaterAprox(std::abs(displacement.y()), std::abs(displacement.x())))
        return calculateSouthIntersection(rectangle, nextRectangle);

    return calculateWestIntersection(rectangle, nextRectangle);
}

std::optional<Vector2> Rectangle::calculateIntersectionIntersectingNextFrame(
        const Rectangle& rectangle, const Vector2& displacement) const {
    const Rectangle nextRectangle(_center + displacement, _width, _height);

    if (not nextRectangle.intersects(rectangle))
        return std::nullopt;

    std::bitset<SidesAmount> collisionInSide;

    if (Math::isGreaterAprox(displacement.x(), 0))
        collisionInSide.set(West);
    else if (Math::isLessAprox(displacement.x(), 0))
        collisionInSide.set(East);

    if (Math::isLessAprox(displacement.y(), 0))
        collisionInSide.set(South);
    else if (Math::isGreaterAprox(displacement.y(), 0))
        collisionInSide.set(North);

    if (collisionInSide.test(North) and rectangle.contains(nextRectangle.axisPoints()[South]))
        return calculateNorthIntersection(rectangle, nextRectangle);

    if (collisionInSide.test(South) and rectangle.contains(nextRectangle.axisPoints()[North]))
        return calculateSouthIntersection(rectangle, nextRectangle);

    if (collisionInSide.test(East) and rectangle.contains(nextRectangle.axisPoints()[West]))
        return calculateEastIntersection(rectangle, nextRectangle);

    if (collisionInSide.test(West) and rectangle.contains(nextRectangle.axisPoints()[East]))
        return calculateWestIntersection(rectangle, nextRectangle);

    if (collisionInSide.test(North) and collisionInSide.test(East))
        return calculateNorthEastIntersection(rectangle, displacement, nextRectangle);

    if (collisionInSide.test(North) and collisionInSide.test(West))
        return calculateNorthWestIntersection(rectangle, displacement, nextRectangle);

    if (collisionInSide.test(South) and collisionInSide.test(East))
        return calculateSouthEastIntersection(rectangle, displacement, nextRectangle);

    return calculateSouthWestIntersection(rectangle, displacement, nextRectangle);
}

Rectangle::Rectangle(Vector2 center, const float width, const float height):
        _center(std::move(center)),
        _width(width),
        _height(height),
        cachedSides(std::nullopt),
        cachedVertices(std::nullopt) {}

Rectangle& Rectangle::setCenter(Vector2 center) {
    if (this->center() != center) {
        _center = std::move(center);
        invalidateCachedValues();
    }

    return *this;
}

const Vector2& Rectangle::center() const { return _center; }

float Rectangle::width() const { return _width; }

Rectangle& Rectangle::setWidth(const float width) {
    if (not Math::isEqualAprox(_width, width)) {
        _width = width;
        invalidateCachedValues();
    }

    return *this;
}

float Rectangle::height() const { return _height; }

Rectangle& Rectangle::setHeight(const float height) {
    if (not Math::isEqualAprox(_height, height)) {
        _height = height;
        invalidateCachedValues();
    }

    return *this;
}

Rectangle::Region Rectangle::regionOfPoint(const Vector2& point) const {
    const auto vertices = this->vertices();

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

const Rectangle::Sides& Rectangle::sides() const {
    if (not cachedSides.has_value())
        const_cast<Rectangle*>(this)->calculateSides();

    return cachedSides.value();
}

const Rectangle::Vertices& Rectangle::vertices() const {
    if (not cachedVertices.has_value())
        const_cast<Rectangle*>(this)->calculateVertices();

    return cachedVertices.value();
}

const Rectangle::AxisPoints& Rectangle::axisPoints() const {
    if (not cachedAxisPoints.has_value())
        const_cast<Rectangle*>(this)->calculateAxisPoints();

    return cachedAxisPoints.value();
}

bool Rectangle::contains(const Vector2& point) const {
    const auto vertices = this->vertices();
    const float minX = std::min(vertices[NorthWest].x(), vertices[SouthWest].x());
    const float maxX = std::max(vertices[NorthEast].x(), vertices[SouthEast].x());
    const float minY = std::min(vertices[NorthEast].y(), vertices[SouthEast].y());
    const float maxY = std::max(vertices[NorthWest].y(), vertices[SouthWest].y());

    return point.x() >= minX && point.x() <= maxX && point.y() >= minY && point.y() <= maxY;
}

std::optional<Rectangle::Side> Rectangle::touches(const Rectangle& rectangle) const {
    const float selfHalfWidth = _width / 2.0f;
    const float selfHalfHeight = _height / 2.0f;

    const float rectHalfWidth = rectangle.width() / 2.0f;
    const float rectHalfHeight = rectangle.height() / 2.0f;

    const float deltaX = std::abs(_center.x() - rectangle._center.x());
    const float deltaY = std::abs(_center.y() - rectangle._center.y());

    const bool barelyTouchingX = Math::isEqualAprox(deltaX, selfHalfWidth + rectHalfWidth);
    const bool barelyTouchingY = deltaY == selfHalfHeight + rectHalfHeight;

    if (barelyTouchingX && Math::isLessOrEqualAprox(deltaY, selfHalfHeight + rectHalfHeight)) {
        if (_center.x() < rectangle._center.x())
            return East;

        return West;
    }

    if (barelyTouchingY && Math::isLessOrEqualAprox(deltaX, selfHalfWidth + rectHalfWidth)) {
        if (_center.y() < rectangle._center.y())
            return North;

        return South;
    }

    return std::nullopt;
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

std::optional<Vector2> Rectangle::intersects(const Rectangle& rectangle,
                                             const Vector2& displacement) const {
    // if (intersects(rectangle))
    //     return calculateIntersectionAlreadyIntersecting(rectangle, displacement);

    return calculateIntersectionIntersectingNextFrame(rectangle, displacement);
}