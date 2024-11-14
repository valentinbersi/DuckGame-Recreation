#pragma once

#include "Shape2D.h"
#include "Types.h"
#include "Vector2.h"


class Segment;
class Rectangle final: public Shape2D {
    float _width, _height;

    /**
     * Calculate the vertices of the rectangle and cache them
     */
    void calculateVertices();

    /**
     * Calculate the sides of the rectangle and cache them, this also calculates the vertices
     */
    void calculateSides();

    /**
     * Calculate the axis points of the rectangle and cache them
     */
    void calculateAxisPoints();

public:
    Rectangle() = delete;
    Rectangle(const Rectangle& other) = delete;
    Rectangle& operator=(const Rectangle& other) = delete;
    Rectangle(Rectangle&& other) noexcept = delete;
    Rectangle& operator=(Rectangle&& other) noexcept = delete;
    ~Rectangle() override = default;

    /**
     * Set the center of the rectangle
     * @param center The new center of the rectangle
     */
    Shape2D& setCenter(Vector2 center) override;

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

    enum class Region { North, NorthEast, East, SouthEast, South, SouthWest, West, NorthWest };

    /**
     * Get in which region of the rectangle a point is
     * @param point a point
     * @return The region of the rectangle the point is in
     * @pre The point is outside the rectangle
     */
    [[nodiscard]] Region regionOfPoint(const Vector2& point) const;


    enum Side { North = 0, East = 1, South = 2, West = 3 };
    constexpr static u8 SidesAmount = 4;
    using Sides = std::array<Segment, SidesAmount>;

    /**
     * Get the sides of a rectangle as segments
     * @return An array of segments representing the sides of the rectangle
     */
    [[nodiscard]] const std::array<Segment, 4>& getSides() const;

    enum Vertex { NorthWest = 0, NorthEast = 1, SouthEast = 2, SouthWest = 3 };
    constexpr static u8 VertexAmount = 4;
    using Vertices = std::array<Vector2, VertexAmount>;

    /**
     * Get the vertices of the rectangle
     * @return An array of vectors representing the vertices of the rectangle
     */
    [[nodiscard]] Vertices getVertices() const;

    constexpr static u8 AxisPoinstAmount = 4;
    using AxisPoints = std::array<Vector2, VertexAmount>;

    /**
     * Get the axis points of the rectangle
     * @return An array of vectors representing the axis points of the rectangle
     */
    [[nodiscard]] AxisPoints getAxisPoints() const;

    /**
     * Check if a point is inside the rectangle
     * @param point a point
     */
    [[nodiscard]] bool contains(const Vector2& point) const override;

    /**
     * Check if this rectangle intersects a circle
     * @param circle a circle
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] bool intersects(const Circle& circle) const override;

    [[nodiscard]] std::optional<IntersectionInfo> intersects(const Circle& circle,
                                                             Vector2 displacement) const override;

    /**
     * Check if this rectangle intersects a rectangle
     * @param rectangle a rectangle
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] bool intersects(const Rectangle& rectangle) const override;

    [[nodiscard]] std::optional<IntersectionInfo> intersects(const Rectangle& rectangle,
                                                             Vector2 displacement) const override;

private:
    std::optional<Sides> cachedSides;
    std::optional<Vertices> cachedVertices;
    std::optional<AxisPoints> cachedAxisPoints;
};
