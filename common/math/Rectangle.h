#pragma once

#include <bitset>

#include "IntersectionInfo.h"
#include "Segment.h"
#include "Types.h"
#include "Vector2.h"

class Line;

class Rectangle final {
    Vector2 _center;
    float _width, _height;

    /**
     * Reset the cached values of the rectangle
     */
    void invalidateCachedValues();

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

    /**
     * Handle the collision when the rectangle is colliding with the north side of the other
     * rectangle
     * @param rectangle The other rectangle
     * @param nextRectangle The next rectangle
     * @param velocityLine The velocity line
     * @return The intersection info
     */
    [[nodiscard]] std::optional<IntersectionInfo> calculateNorthIntersection(
            const Rectangle& rectangle, const Rectangle& nextRectangle,
            const Line& velocityLine) const;

    /**
     * Handle the collision when the rectangle is colliding with the south side of the other
     * rectangle
     * @param rectangle The other rectangle
     * @param nextRectangle The next rectangle
     * @param velocityLine The velocity line
     * @return The intersection info
     */
    [[nodiscard]] std::optional<IntersectionInfo> calculateSouthIntersection(
            const Rectangle& rectangle, const Rectangle& nextRectangle,
            const Line& velocityLine) const;

    /**
     * Handle the collision when the rectangle is colliding with the east side of the other
     * rectangle
     * @param rectangle The other rectangle
     * @param nextRectangle The next rectangle
     * @param velocityLine The velocity line
     * @return The intersection info
     */
    [[nodiscard]] std::optional<IntersectionInfo> calculateEastIntersection(
            const Rectangle& rectangle, const Rectangle& nextRectangle,
            const Line& velocityLine) const;

    /**
     * Handle the collision when the rectangle is colliding with the west side of the other
     * rectangle
     * @param rectangle The other rectangle
     * @param nextRectangle The next rectangle
     * @param velocityLine The velocity line
     * @return The intersection info
     */
    [[nodiscard]] std::optional<IntersectionInfo> calculateWestIntersection(
            const Rectangle& rectangle, const Rectangle& nextRectangle,
            const Line& velocityLine) const;

    /**
     * Handle the collision when the rectangle is colliding with the north east side of the other
     * rectangle
     * @param rectangle The other rectangle
     * @param displacement The displacement of the rectangle
     * @param nextRectangle The next rectangle
     * @param velocityLine The velocity line
     * @return The intersection info
     */
    [[nodiscard]] std::optional<IntersectionInfo> calculateNorthEastIntersection(
            const Rectangle& rectangle, const Vector2& displacement, const Rectangle& nextRectangle,
            const Line& velocityLine) const;

    /**
     * Handle the collision when the rectangle is colliding with the north west side of the other
     * rectangle
     * @param rectangle The other rectangle
     * @param displacement The displacement of the rectangle
     * @param nextRectangle The next rectangle
     * @param velocityLine The velocity line
     * @return The intersection info
     */
    [[nodiscard]] std::optional<IntersectionInfo> calculateNorthWestIntersection(
            const Rectangle& rectangle, const Vector2& displacement, const Rectangle& nextRectangle,
            const Line& velocityLine) const;

    /**
     * Handle the collision when the rectangle is colliding with the south east side of the other
     * rectangle
     * @param rectangle The other rectangle
     * @param displacement The displacement of the rectangle
     * @param nextRectangle The next rectangle
     * @param velocityLine The velocity line
     * @return The intersection info
     */
    [[nodiscard]] std::optional<IntersectionInfo> calculateSouthEastIntersection(
            const Rectangle& rectangle, const Vector2& displacement, const Rectangle& nextRectangle,
            const Line& velocityLine) const;

    /**
     * Handle the collision when the rectangle is colliding with the south west side of the other
     * rectangle
     * @param rectangle The other rectangle
     * @param displacement The displacement of the rectangle
     * @param nextRectangle The next rectangle
     * @param velocityLine The velocity line
     * @return The intersection info
     */
    [[nodiscard]] std::optional<IntersectionInfo> calculateSouthWestIntersection(
            const Rectangle& rectangle, const Vector2& displacement, const Rectangle& nextRectangle,
            const Line& velocityLine) const;

public:
    Rectangle() = delete;
    Rectangle(const Rectangle& other) = delete;
    Rectangle& operator=(const Rectangle& other) = delete;
    Rectangle(Rectangle&& other) noexcept = delete;
    Rectangle& operator=(Rectangle&& other) noexcept = delete;
    ~Rectangle() = default;

    /**
     * Construct a rectangle with the given center, width and height
     * @param center The center of the rectangle
     * @param width The width of the rectangle
     * @param height The height of the rectangle
     */
    Rectangle(Vector2 center, float width, float height);

    /**
     * Get the center of the rectangle
     * @return The center of the rectangle
     */
    [[nodiscard]] const Vector2& center() const;

    /**
     * Set the center of the rectangle
     * @param center The new center of the rectangle
     */
    Rectangle& setCenter(Vector2 center);

    /**
     * Get the width of the rectangle
     * @return The width and height of the rectangle
     */
    [[nodiscard]] float width() const;

    /**
     * Set the width of the rectangle
     * @param width The new width of the rectangle
     * @return The rectangle
     */
    Rectangle& setWidth(float width);

    /**
     * Get the height of the rectangle
     * @return The height of the rectangle
     */
    [[nodiscard]] float height() const;

    /**
     * Set the height of the rectangle
     * @param height The new height of the rectangle
     * @return The rectangle
     */
    Rectangle& setHeight(float height);

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
     * Get the sides of a rectangle as segments.
     * @return An array of segments representing the sides of the rectangle
     */
    [[nodiscard]] const Sides& sides() const;

    enum Vertex { NorthWest = 0, NorthEast = 1, SouthEast = 2, SouthWest = 3 };
    constexpr static u8 VertexAmount = 4;
    using Vertices = std::array<Vector2, VertexAmount>;

    /**
     * Get the vertices of the rectangle
     * @return An array of vectors representing the vertices of the rectangle
     */
    [[nodiscard]] const Vertices& vertices() const;

    constexpr static u8 AxisPoinstAmount = 4;
    using AxisPoints = std::array<Vector2, VertexAmount>;

    /**
     * Get the axis points of the rectangle
     * @return An array of vectors representing the axis points of the rectangle
     */
    [[nodiscard]] const AxisPoints& axisPoints() const;

    /**
     * Check if a point is inside the rectangle
     * @param point a point
     */
    [[nodiscard]] bool contains(const Vector2& point) const;

    /**
     * Check if this rectangle intersects a rectangle
     * @param rectangle a rectangle
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] bool intersects(const Rectangle& rectangle) const;

    /**
     * Check if this rectangle intersects with other rectangle when having a displacement and get
     * the intersection info
     * @param rectangle a rectangle
     * @param displacement the displacement of the rectangle
     * @return The intersection info if the rectangles intersect, std::nullopt otherwise
     */
    [[nodiscard]] std::optional<IntersectionInfo> intersects(const Rectangle& rectangle,
                                                             const Vector2& displacement) const;

private:
    std::optional<Sides> cachedSides;
    std::optional<Vertices> cachedVertices;
    std::optional<AxisPoints> cachedAxisPoints;
};
