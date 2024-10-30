#pragma once

#include "Shape2D.h"
#include "Types.h"
#include "Vector2.h"

class Rectangle final: public Shape2D {
    constexpr static u8 VertexAmount = 4;

    float _width, _height;

    /**
     * Check if the two rectangles overlap on the given axis
     * @param rect2Vertices The vertices of the second rectangle
     * @param axis The axis to check
     * @return True if the rectangles overlap on the axis, false otherwise
     */
    [[nodiscard]] bool overlapOnAxis(const std::array<Vector2, VertexAmount>& rect2Vertices,
                                     const Vector2& axis) const;

    /**
     * Get the corners of the rectangle
     * @return The corners of the rectangle
     */
    [[nodiscard]] std::array<Vector2, VertexAmount> vertices() const;

public:
    struct Vertex {
        enum Value : u8 { TopLeft = 0, TopRight = 1, BottomLeft = 2, BottomRight = 3, Invalid = 4 };

        Vertex() = delete;
        Vertex(const Vertex& other);
        Vertex& operator=(const Vertex& other);
        Vertex(Vertex&& other) noexcept;
        Vertex& operator=(Vertex&& other) noexcept;

        /**
         * Construct a vertex with the given value
         * @param value The value of the vertex
         */
        // cppcheck-suppress noExplicitConstructor
        Vertex(Value value);

        /**
         * Compare two vertices
         * @param other The other vertex to compare
         * @return True if the vertices are equal, false otherwise
         */
        bool operator==(Vertex other) const;

        /**
         * Compare two vertices
         * @param other The other vertex to compare
         * @return True if the vertices are not equal, false otherwise
         */
        bool operator!=(Vertex other) const;

        /**
         * Convert the vertex to a value
         */
        // cppcheck-suppress noExplicitConstructor
        operator Value() const;

        /**
         * Convert the vertex to a boolean
         * @return True if the vertex is valid, false otherwise
         */
        // cppcheck-suppress noExplicitConstructor
        operator bool() const;

        /**
         * Check if the given value is a valid vertex
         * @param value The value to check
         * @return True if the value is a valid vertex, false otherwise
         */
        static bool isValidValue(u8 value);

    private:
        Value value;
    };

    Rectangle() = delete;
    Rectangle(const Rectangle& other);
    Rectangle& operator=(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;
    Rectangle& operator=(Rectangle&& other) noexcept;
    ~Rectangle() override = default;

    /**
     * Construct a rectangle with the given center, width and height
     * @param center The center of the rectangle
     * @param rotation The rotation of the rectangle
     * @param width The width of the rectangle
     * @param height The height of the rectangle
     */
    Rectangle(Vector2 center, float rotation, float width, float height);

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

    /**
     * Check if this rectangle intersects with a capsule
     * @param capsule a capsule
     * @return True if the shapes intersect, false otherwise
     */
    [[nodiscard]] bool intersects(const Capsule& capsule) const override;
};
