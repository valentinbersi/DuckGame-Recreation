#include "Line.h"

#include <algorithm>

#include "Math.h"
#include "Segment.h"

Line::Line(Vector2 direction, Vector2 passingPoint):
        _direction(std::move(direction)), _pasingPoint(std::move(passingPoint)) {}

Line::Line(const Segment& segment): _direction(segment.end()), _pasingPoint(segment.start()) {}

const Vector2& Line::direction1() const { return _direction; }

void Line::setDirection(Vector2 direction) { this->_direction = std::move(direction); }

const Vector2& Line::pasingPoint() const { return _pasingPoint; }

void Line::setPasingPoint(Vector2 pasingPoint) { _pasingPoint = std::move(pasingPoint); }

std::optional<Vector2> Line::intersection(const Line& other) const {
    // Line 1: _passingPoint + t * _direction
    // Line 2: other._passingPoint + u * other._direction
    // We need to solve for t and u where the lines intersect

    // This are coefficients of the lines in the form ax + by = c
    const float a1 = _direction.y();
    const float b1 = -_direction.x();
    const float c1 = a1 * _pasingPoint.x() + b1 * _pasingPoint.y();

    const float a2 = other._direction.y();
    const float b2 = -other._direction.x();
    const float c2 = a2 * other._pasingPoint.x() + b2 * other._pasingPoint.y();

    const float determinant = a1 * b2 - a2 * b1;

    if (Math::isZeroAprox(std::abs(determinant))) {
        if (Math::isZeroAprox(std::abs(c1 - c2)))
            return Vector2::NANV;  // Coincident lines

        return std::nullopt;  // Just parallel
    }

    const float x = (b2 * c1 - b1 * c2) / determinant;
    const float y = (a1 * c2 - a2 * c1) / determinant;

    return Vector2(x, y);  // Intersection point
}

std::optional<Vector2> Line::intersection(const Segment& segment) const {
    // Line: _passingPoint + t * _direction
    // Segment: segment.start() + u * segmentDirection
    const Vector2& segmentDirection = segment.end() - segment.start();

    // Solve for t and u
    float denom = _direction.x() * segmentDirection.y() - _direction.y() * segmentDirection.x();
    if (Math::isZeroAprox(std::abs(denom))) {
        if (intersection(segment.start()))
            return Vector2::NANV;  // Coincident lines

        return std::nullopt;  // Parallel or coincident
    }

    const float t = ((segment.start().x() - _pasingPoint.x()) * segmentDirection.y() -
                     (segment.start().y() - _pasingPoint.y()) * segmentDirection.x()) /
                    denom;

    if (const float u = ((segment.start().x() - _pasingPoint.x()) * _direction.y() -
                         (segment.start().y() - _pasingPoint.y()) * _direction.x()) /
                        denom;
        u < 0.0f or u > 1.0f)
        return std::nullopt;  // Intersection point is not on the segment

    return _pasingPoint + _direction * t;  // Intersection point
}

bool Line::intersection(const Vector2& point) const {
    // Line: _passingPoint + t * _direction
    // Check if the point lies on the line

    // Calculate t for the x and y coordinates
    const float tX = (point.x() - _pasingPoint.x()) / _direction.x();
    const float tY = (point.y() - _pasingPoint.y()) / _direction.y();

    // If tX and tY are approximately equal, the point lies on the line
    return Math::isEqualAprox(tX, tY);
}
