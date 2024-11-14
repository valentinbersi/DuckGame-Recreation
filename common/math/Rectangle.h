#pragma once

#include "Shape2D.h"
#include "Types.h"
#include "Vector2.h"


class Segment;
class Rectangle final: public Shape2D {


    float _width, _height;

public:
    constexpr static u8 SidesAmount = 4;

    Rectangle() = delete;
    Rectangle(const Rectangle& other) = delete;
    Rectangle& operator=(const Rectangle& other) = delete;
    Rectangle(Rectangle&& other) noexcept = delete;
    Rectangle& operator=(Rectangle&& other) noexcept = delete;
    ~Rectangle() override = default;

    /**
     * Construct a rectangle with the given center, width and height
     * @param center The center of the rectangle
     * @param width The width of the rectangle
     * @param height The height of the rectangle
     */
    Rectangle(Vector2 center, float width, float height);

    /**
     * Get the width of the rectangle
     * @return The width and height of the rectangle
     */
    [[nodiscard]] float width() const;

    /**
     * Get the height of the rectangle
     * @return The height of the rectangle
     */
    [[nodiscard]] float height() const;

    enum Sides { North = 0, East = 1, South = 2, West = 3 };

    /**
     * Get the sides of a rectangle as segments
     * @return An array of segments representing the sides of the rectangle
     */
    [[nodiscard]] std::array<Segment, SidesAmount> getSides() const;

    /**
     * Check if this rectangle intersects a circle
     * @param circle a circle
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] bool intersects(const Circle& circle) const override;

    /**
     * Check if this rectangle intersects a rectangle
     * @param rectangle a rectangle
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] bool intersects(const Rectangle& rectangle) const override;
};
