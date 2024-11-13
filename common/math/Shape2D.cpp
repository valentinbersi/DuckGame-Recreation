#include "Shape2D.h"

#include <utility>

#include "Circle.h"
#include "Rectangle.h"

Shape2D::Shape2D(Vector2 center): _center(std::move(center)) {}

const Vector2& Shape2D::center() const { return _center; }

Shape2D& Shape2D::center(Vector2 center) {
    _center = std::move(center);
    return *this;
}

bool Shape2D::intersects(const Shape2D& shape) const try {
    return intersects(dynamic_cast<const Circle&>(shape));
} catch (const std::bad_cast&) {
    return intersects(dynamic_cast<const Rectangle&>(shape));
}
