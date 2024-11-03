#pragma once
#include <memory>

#include "Vector2.h"

class Circle;
class Rectangle;
class Capsule;

/**
 * Common interface for all shapes in 2D space
 */
class Shape2D {
    Vector2 _center;
    float _rotation;

protected:
    Shape2D(const Shape2D& other);
    Shape2D& operator=(const Shape2D& other);
    Shape2D(Shape2D&& other) noexcept;
    Shape2D& operator=(Shape2D&& other) noexcept;

    /**
     * Construct a shape with a center and rotation
     * @param center the center of the shape
     * @param rotation the rotation of the shape
     */
    Shape2D(Vector2 center, float rotation);

public:
    Shape2D() = delete;
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
     * Get the rotation of the shape
     * @return the rotation of the shape
     */
    [[nodiscard]] float rotation() const;

    /**
     * Set the rotation of the shape
     * @param rotation the new rotation of the shape
     * @return this shape
     */
    Shape2D& rotation(float rotation);

    /**
     * Check if this shape intersects another shape
     * @param shape The other shape
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] bool intersects(const Shape2D& shape) const;

    /**
     * Check if this shape intersects a circle
     * @param circle a circle
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] virtual bool intersects(const Circle& circle) const = 0;

    /**
     * Check if this shape intersects a rectangle
     * @param rectangle a rectangle
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] virtual bool intersects(const Rectangle& rectangle) const = 0;

    /**
     * Check if this shape intersects with a capsule
     * @param capsule a capsule
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] virtual bool intersects(const Capsule& capsule) const = 0;

    /**
     * Clone this shape
     * @return a clone of this shape
     */
    [[nodiscard]] virtual std::unique_ptr<Shape2D> clone() const = 0;
};
