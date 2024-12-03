#include "Segment2D.h"

#include <utility>

#include "Math.h"

Segment2D::Segment2D(Vector2 begin, Vector2 end): start_(std::move(begin)), end_(std::move(end)) {}

Vector2 Segment2D::start() const { return start_; }

Vector2 Segment2D::end() const { return end_; }

std::optional<Vector2> Segment2D::intersects(const Segment2D& other) const {
    const Vector2 d1 = end_ - start_;
    const Vector2 d2 = other.end_ - other.start_;
    const Vector2 delta = other.start_ - start_;

    const float crossD1D2 = d1.cross(d2);

    if (Math::isZeroAprox(std::abs(crossD1D2)))
        return std::nullopt;

    const float t = delta.cross(d2) / crossD1D2;
    if (const float u = delta.cross(d1) / crossD1D2; t >= 0 and t <= 1 and u >= 0 and u <= 1)
        return start_ + d1 * t;

    return std::nullopt;
}

Segment2D Segment2D::cut(const float newLength) {
    return {start_, start_ + (end_ - start_).normalized() * newLength};
}

bool Segment2D::operator==(const Segment2D& other) const {
    return start_ == other.start_ and end_ == other.end_;
}
