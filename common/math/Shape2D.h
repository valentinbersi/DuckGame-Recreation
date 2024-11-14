#pragma once

#include <optional>

#include "Vector2.h"

class Circle;
class Rectangle;
class Capsule;

struct IntersectionInfo {
    Vector2 safeDisplacement;
    Vector2 surfaceNormal;

    IntersectionInfo(Vector2 safeDisplacement, Vector2 surfaceNormal);
};

/**
 * Common interface for all shapes in 2D space
 */
class Shape2D {
    Vector2 _center;

protected:
    /**
     * Construct a shape with a center and rotation
     * @param center the center of the shape
     */
    explicit Shape2D(Vector2 center);

public:
    Shape2D() = delete;
    Shape2D(const Shape2D& other) = delete;
    Shape2D& operator=(const Shape2D& other) = delete;
    Shape2D(Shape2D&& other) noexcept = delete;
    Shape2D& operator=(Shape2D&& other) noexcept = delete;
    virtual ~Shape2D() = default;

    /**
     * Get the center of the shape
     * @return the center of the shape
     */
    [[nodiscard]] const Vector2& center() const;

    /**
     * Set the center of the shape
     * @param center the new center of the shape
     * @return this shape
     */
    Shape2D& center(Vector2 center);

    /**
     * Check if this shape intersects another shape
     * @param shape The other shape
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] bool intersects(const Shape2D& shape) const;

    /**
     * Check if this shape intersects with another shape when having a displacement
     * @param shape The other shape
     * @param displacement The displacement of this shape
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] std::optional<IntersectionInfo> intersects(const Shape2D& shape,
                                                             Vector2 displacement) const;

    /**
     * Check if this shape intersects a circle
     * @param circle a circle
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] virtual bool intersects(const Circle& circle) const = 0;

    /**
     * Check if this shape intersects a circle
     * @param circle a circle
     * @param displacement The displacement of this shape
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] virtual std::optional<IntersectionInfo> intersects(
            const Circle& circle, Vector2 displacement) const = 0;

    /**
     * Check if this shape intersects a rectangle
     * @param rectangle a rectangle
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] virtual bool intersects(const Rectangle& rectangle) const = 0;

    /**
     * Check if this shape intersects a rectangle
     * @param rectangle a rectangle
     * @param displacement The displacement of this shape
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] virtual std::optional<IntersectionInfo> intersects(
            const Rectangle& rectangle, Vector2 displacement) const = 0;
};
