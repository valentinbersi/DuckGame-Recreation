#pragma once

#include "Shape2D.h"
#include "Vector2.h"

class Circle final: public Shape2D {
    float _radius;

    /**
     * Check if this circle touches but does not overlap another circle
     * @param circle a circle
     * @return True if the circles touch, false otherwise
     */
    bool touches(const Circle& circle) const;

public:
    Circle() = delete;
    Circle(const Circle& other) = delete;
    Circle& operator=(const Circle& other) = delete;
    Circle(Circle&& other) noexcept = delete;
    Circle& operator=(Circle&& other) noexcept = delete;
    ~Circle() override = default;

    /**
     * Construct a circle with the given radius
     * @param center The center of the circle
     * @param rotation The rotation of the circle
     * @param radius The radius of the circle
     */
    Circle(Vector2 center, float radius);

    /**
     * Get the radius of the circle
     * @return The radius of the circle
     */
    [[nodiscard]] float radius() const;

    /**
     * Set the radius of the circle
     * @param radius The new radius of the circle
     */
    Circle& radius(float radius);

    /**
     * Check if this circle intersects with a circle
     * @param circle a circle
     * @return True if the circles intersect, false otherwise
     */
    [[nodiscard]] bool intersects(const Circle& circle) const override;

    /**
     * Check if this circle intersects with a circle
     * @param circle a circle
     * @param displacement The displacement of the circle
     * @return An IntersectionInfo with information about the collision if it happened
     */
    [[nodiscard]] IntersectionInfo intersects(const Circle& circle,
                                              Vector2 displacement) const override;

    /**
     * Check if this circle intersects with a rectangle
     * @param rectangle a rectangle
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] bool intersects(const Rectangle& rectangle) const override;

    /**
     * Check if this circle intersects with a rectangle
     * @param rectangle a rectangle
     * @param displacement The displacement of the circle
     * @return An IntersectionInfo with information about the collision if it happened
     */
    [[nodiscard]] IntersectionInfo intersects(const Rectangle& rectangle,
                                              Vector2 displacement) const override;
};
