#pragma once

#include "Shape2D.h"
#include "Vector2.h"

class Circle final: public Shape2D {
    float _radius;

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
     * Check if this circle intersects with a rectangle
     * @param rectangle a rectangle
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] bool intersects(const Rectangle& rectangle) const override;
};
