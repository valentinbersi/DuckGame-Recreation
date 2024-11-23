#pragma once

#include <optional>

#include "IntersectionInfo.h"
#include "Ray2D.h"
#include "Vector2.h"

class Rectangle final {
    Vector2 _position;
    Vector2 _size;

public:
    Rectangle() = delete;
    Rectangle(const Rectangle& other);
    Rectangle& operator=(const Rectangle& other);
    Rectangle(Rectangle&& other) noexcept;
    Rectangle& operator=(Rectangle&& other) noexcept;
    ~Rectangle() = default;

    /**
     * Construct a rectangle with the given center, width and height
     * @param center The center of the rectangle
     * @param width The width of the rectangle
     * @param height The height of the rectangle
     */
    Rectangle(const Vector2& center, float width, float height);

    /**
     * Construct a rectangle with the given position and size
     * @param position The position of the rectangle, this is the top left corner
     * @param size The size of the rectangle
     */
    Rectangle(Vector2 position, Vector2 size);

    /**
     * Get the position of the rectangle
     * @return the position of the rectangle
     */
    Vector2 position() const;

    /**
     * Set the position of the rectangle
     * @param position the new position
     * @return a reference to this rectangle
     */
    Rectangle& setPosition(Vector2 position);

    /**
     * Get the size of the rectangle
     * @return the size of the rectangle
     */
    Vector2 size() const;

    /**
     * Set the size of the rectangle
     * @param size the new size
     * @return a reference to this rectangle
     */
    Rectangle& setSize(Vector2 size);

    /**
     * Get the center of the rectangle
     * @return the center of the rectangle
     */
    Vector2 center() const;

    /**
     * Set the center of the rectangle
     * @param center The new center of the rectangle
     * @return A reference to this rectangle
     */
    Rectangle& setCenter(const Vector2& center);

    /**
     * Check if a point is contained by the rectangle
     * @param point The point to check
     * @return true if the point is contained by the rectangle, false otherwise
     */
    [[nodiscard]] bool contains(const Vector2& point) const;

    /**
     * Check if a rectangle overlaps with this rectangle
     * @param rectangle The rectangle to check
     * @return true if the rectangles overlap, false otherwise
     */
    [[nodiscard]] bool overlaps(const Rectangle& rectangle) const;

    /**
     * Check if this rectangle overlaps with another rectangle while moving with a certain velocity
     * @param rectangle The rectangle to check
     * @return
     */
    [[nodiscard]] std::optional<IntersectionInfo> overlaps(const Rectangle& rectangle,
                                                           const Vector2& displacement,
                                                           float delta) const;

    /**
     * Check if a segment overlaps with this rectangle
     * @param ray The segment to check
     * @return true if the segment overlaps with the rectangle, false otherwise
     */
    [[nodiscard]] std::optional<IntersectionInfo> overlaps(const Ray2D& ray) const;

    /**
     * Checks if two rectangles are equal aproximately
     * @param other The rectangle to compare to
     * @return true if the rectangles are equal aproximately, false otherwise
     */
    bool operator==(const Rectangle& other) const;
};
