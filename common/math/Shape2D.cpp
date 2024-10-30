#include "Shape2D.h"

#include <utility>

#include "Capsule.h"
#include "Circle.h"
#include "Rectangle.h"

Shape2D::Shape2D(const Shape2D& other) = default;

Shape2D& Shape2D::operator=(const Shape2D& other) = default;

Shape2D::Shape2D(Shape2D&& other) noexcept = default;

Shape2D& Shape2D::operator=(Shape2D&& other) noexcept = default;

Shape2D::Shape2D(Vector2 center, const float rotation):
        _center(std::move(center)), _rotation(rotation) {}

const Vector2& Shape2D::center() const { return _center; }

Shape2D& Shape2D::center(Vector2 center) {
    _center = std::move(center);
    return *this;
}

float Shape2D::rotation() const { return _rotation; }

Shape2D& Shape2D::rotation(const float rotation) {
    _rotation = rotation;
    return *this;
}

bool Shape2D::intersects(const Shape2D& shape) const {
    if (const auto circle = dynamic_cast<const Circle*>(&shape))
        return intersects(*circle);

    if (const auto rectangle = dynamic_cast<const Rectangle*>(&shape))
        return intersects(*rectangle);

    return intersects(*dynamic_cast<const Capsule*>(&shape));
}
