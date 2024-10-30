#include "Capsule.h"

#include <utility>

#include "Circle.h"
#include "Rectangle.h"

Capsule::Capsule(const Capsule& other) = default;

Capsule& Capsule::operator=(const Capsule& other) = default;

Capsule::Capsule(Capsule&& other) noexcept:
        Shape2D(std::move(other)), _radius(other._radius), _heigth(other._heigth) {}

Capsule& Capsule::operator=(Capsule&& other) noexcept {
    Shape2D::operator=(std::move(other));
    _radius = other._radius;
    _heigth = other._heigth;
    _radius = 0;
    _heigth = 0;
    return *this;
}


Capsule::Capsule(Vector2 center, const float rotation, const float radius, const float height):
        Shape2D(std::move(center), rotation), _radius(radius), _heigth(height) {}

float Capsule::radius() const { return _radius; }

float Capsule::height() const { return _heigth; }

bool Capsule::intersects(const Circle& circle) const {
    if (Circle(center() + Vector2(0, _heigth / 2).rotated(rotation()), _radius).intersects(circle))
        return true;

    if (Circle(center() + Vector2(0, -_heigth / 2).rotated(rotation()), _radius).intersects(circle))
        return true;

    return Rectangle(center(), rotation(), _radius * 2, _heigth).intersects(circle);
}

bool Capsule::intersects(const Rectangle& rectangle) const {
    if (Circle(center() + Vector2(0, _heigth / 2).rotated(rotation()), _radius)
                .intersects(rectangle))
        return true;

    if (Circle(center() + Vector2(0, -_heigth / 2).rotated(rotation()), _radius)
                .intersects(rectangle))
        return true;

    return Rectangle(center(), rotation(), _radius * 2, _heigth).intersects(rectangle);
}

bool Capsule::intersects(const Capsule& capsule) const {
    const Circle thisTopCircle(center() + Vector2(0, _heigth / 2).rotated(rotation()), _radius);
    const Circle thisBottomCircle(center() + Vector2(0, -_heigth / 2).rotated(rotation()), _radius);
    const Rectangle thisRectangle(center(), rotation(), _radius * 2, _heigth);

    const Circle capsuleTopCircle(
            capsule.center() + Vector2(0, capsule._heigth / 2).rotated(capsule.rotation()),
            capsule._radius);
    const Circle capsuleBottomCircle(
            capsule.center() + Vector2(0, -capsule._heigth / 2).rotated(capsule.rotation()),
            capsule._radius);
    const Rectangle capsuleRectangle(capsule.center(), capsule.rotation(), capsule._radius * 2,
                                     capsule._heigth);

    return thisTopCircle.intersects(capsuleTopCircle) ||
           thisTopCircle.intersects(capsuleBottomCircle) ||
           thisBottomCircle.intersects(capsuleTopCircle) ||
           thisBottomCircle.intersects(capsuleBottomCircle) ||
           thisTopCircle.intersects(capsuleRectangle) ||
           thisBottomCircle.intersects(capsuleRectangle) ||
           thisRectangle.intersects(capsuleTopCircle) ||
           thisRectangle.intersects(capsuleBottomCircle) ||
           thisRectangle.intersects(capsuleRectangle);
}
