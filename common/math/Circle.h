#pragma once

#include "Rectangle.h"
#include "Shape2D.h"
#include "Vector2.h"

class Segment;

class Circle final: public Shape2D {
    float _radius;

    /**
     * Calculates the axis points of a circle and caches them
     */
    void calculateAxisPoints();

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
     * Set the center of the circle
     * @param center The new center of the circle
     * @return This circle
     */
    Shape2D& setCenter(Vector2 center) override;

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
     * Check if this circle contains a point
     * @param point a point
     * @return True if the circle contains the point, false otherwise
     */
    [[nodiscard]] bool contains(const Vector2& point) const override;

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
    [[nodiscard]] std::optional<IntersectionInfo> intersects(const Circle& circle,
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
    [[nodiscard]] std::optional<IntersectionInfo> intersects(const Rectangle& rectangle,
                                                             Vector2 displacement) const override;

    enum AxisPoint { North = 0, East = 1, South = 2, West = 3 };
    constexpr static u8 AxisPointAmount = 4;
    using AxisPoints = std::array<Vector2, AxisPointAmount>;

    /**
     * Get the axis points of this circle
     */
    AxisPoints getAxisPoints();

private:
    std::optional<AxisPoints> cachedAxisPoints;
};
