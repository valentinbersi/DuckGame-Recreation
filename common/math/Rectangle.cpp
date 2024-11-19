#include "Rectangle.h"

#include <algorithm>
#include <utility>

#include "IntersectionInfo.h"
#include "Math.h"

Rectangle::Rectangle(const Vector2& center, const float width, const float height):
        position(center - Vector2(width / 2, height / 2)), size(width, height) {
    if (width < 0 or height < 0)
        throw std::invalid_argument("Width and height must be positive");
}

Rectangle::Rectangle(Vector2 position, Vector2 size):
        position(std::move(position)), size(std::move(size)) {
    if (size.x() < 0 or size.y() < 0)
        throw std::invalid_argument("Size must be positive");
}

Rectangle& Rectangle::setCenter(const Vector2& center) {
    position = center - size / 2;
    return *this;
}

bool Rectangle::contains(const Vector2& point) const {
    return point.x() >= position.x() and point.y() >= position.y() and
           point.x() < position.x() + size.x() and point.y() < position.y() + size.y();
}

bool Rectangle::overlaps(const Rectangle& rectangle) const {
    return position.x() < rectangle.position.x() + rectangle.size.x() and
           position.x() + size.x() > rectangle.position.x() and
           position.y() < rectangle.position.y() + rectangle.size.y() and
           position.y() + size.y() > rectangle.position.y();
}

std::optional<IntersectionInfo> Rectangle::overlaps(const Rectangle& rectangle,
                                                    const Vector2& displacement,
                                                    const float delta) const {
    if (displacement.isZero())
        return std::nullopt;

    const Rectangle expandedRectangle(rectangle.position - size / 2, rectangle.size + size);

    if (std::optional<IntersectionInfo> intersectionInfo =
                expandedRectangle.overlaps(Ray2D(position + size / 2, displacement * delta))) {
        if (intersectionInfo->tHitNear < 1.0f and intersectionInfo->tHitNear >= 0)
            return intersectionInfo;
    }

    return std::nullopt;
}

std::optional<IntersectionInfo> Rectangle::overlaps(const Ray2D& ray) const {
    IntersectionInfo info{};

    Vector2 tNear((position - ray.origin()) / ray.direction());
    Vector2 tFar((position + size - ray.origin()) / ray.direction());

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

    info.tHitNear = tHitNear;
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
