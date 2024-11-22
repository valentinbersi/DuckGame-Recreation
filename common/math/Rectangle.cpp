#include "Rectangle.h"

#include <algorithm>
#include <utility>

#include "IntersectionInfo.h"
#include "Math.h"

Rectangle::Rectangle(const Rectangle& other) = default;

Rectangle& Rectangle::operator=(const Rectangle& other) {
    if (this == &other)
        return *this;

    _position = other._position;
    _size = other._size;
    return *this;
}

Rectangle::Rectangle(Rectangle&& other) noexcept: _position(std::move(other._position)), _size(std::move(other._size)) {}

Rectangle& Rectangle::operator=(Rectangle&& other) noexcept {
    if (this == &other)
        return *this;

    _position = std::move(other._position);
    _size = std::move(other._size);
    return *this;
}

Rectangle::Rectangle(const Vector2& center, const float width, const float height):
        _position(center - Vector2(width / 2, height / 2)), _size(width, height) {
    if (width < 0 or height < 0)
        throw std::invalid_argument("Width and height must be positive");
}

Rectangle::Rectangle(Vector2 position, Vector2 size):
        _position(std::move(position)), _size(std::move(size)) {
    if (size.x() < 0 or size.y() < 0)
        throw std::invalid_argument("Size must be positive");
}

Vector2 Rectangle::position() const {
    return _position;
}

Rectangle& Rectangle::setPosition(Vector2 position) {
    _position = std::move(position);
    return *this;
}

Vector2 Rectangle::size() const {
    return _size;
}

Rectangle& Rectangle::setSize(Vector2 size) {
    _size = std::move(size);
    return *this;
}

Vector2 Rectangle::center() const {
    return _position + _size / 2;
}

Rectangle& Rectangle::setCenter(const Vector2& center) {
    _position = center - _size / 2;
    return *this;
}

bool Rectangle::contains(const Vector2& point) const {
    return point.x() >= _position.x() and point.y() >= _position.y() and
           point.x() < _position.x() + _size.x() and point.y() < _position.y() + _size.y();
}

bool Rectangle::overlaps(const Rectangle& rectangle) const {
    return _position.x() < rectangle._position.x() + rectangle._size.x() and
           _position.x() + _size.x() > rectangle._position.x() and
           _position.y() < rectangle._position.y() + rectangle._size.y() and
           _position.y() + _size.y() > rectangle._position.y();
}

std::optional<IntersectionInfo> Rectangle::overlaps(const Rectangle& rectangle,
                                                    const Vector2& displacement,
                                                    const float delta) const {
    if (displacement.isZero())
        return std::nullopt;

    const Rectangle expandedRectangle(rectangle._position - _size / 2, rectangle._size + _size);

    if (std::optional<IntersectionInfo> intersectionInfo =
                expandedRectangle.overlaps(Ray2D(_position + _size / 2, displacement * delta))) {
        if (intersectionInfo->contactTime < 1.0f and intersectionInfo->contactTime >= 0)
            return intersectionInfo;
    }

    return std::nullopt;
}

std::optional<IntersectionInfo> Rectangle::overlaps(const Ray2D& ray) const {
    IntersectionInfo info{};

    Vector2 tNear((_position - ray.origin()) / ray.direction());
    Vector2 tFar((_position + _size - ray.origin()) / ray.direction());

    if (std::isnan(tFar.y()) or std::isnan(tFar.x()))
        return std::nullopt;

    if (std::isnan(tNear.y()) or std::isnan(tNear.x()))
        return std::nullopt;

    if (tNear.x() > tFar.x())
        tNear.swapX(tFar);

    if (tNear.y() > tFar.y())
        tNear.swapY(tFar);

    if (tNear.x() > tFar.y() or tNear.y() > tFar.x())
        return std::nullopt;

    const float tHitNear = std::max(tNear.x(), tNear.y());
    if (const float tHitFar = std::min(tFar.x(), tFar.y()); tHitFar < 0)
        return std::nullopt;

    info.contactTime = tHitNear;
    info.contactPoint = ray.origin() + tHitNear * ray.direction();

    if (tNear.x() > tNear.y()) {
        if (ray.direction().x() < 0)
            info.contactNormal = Vector2::RIGHT;
        else
            info.contactNormal = Vector2::LEFT;
    } else if (tNear.x() < tNear.y()) {
        if (ray.direction().y() < 0)
            info.contactNormal = Vector2::DOWN;
        else
            info.contactNormal = Vector2::UP;
    }

    return info;
}
