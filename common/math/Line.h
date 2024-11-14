#pragma once

#include <optional>

#include "Vector2.h"


class Segment;

class Line {
    Vector2 _direction;
    Vector2 _pasingPoint;

public:
    Line() = delete;
    Line(const Line& other) = delete;
    Line(Line&& other) noexcept = delete;
    Line& operator=(const Line& other) = delete;
    Line& operator=(Line&& other) noexcept = delete;

    /**
     * Construct a new Line object
     * @param direction The direction of the line
     * @param passingPoint A point that the line passes through
     */
    explicit Line(Vector2 direction, Vector2 passingPoint);

    /**
     * Construct a new Line object
     * @param segment A segment that the line passes through
     */
    explicit Line(const Segment& segment);

    /**
     * Get the direction of the line
     * @return The direction of the line
     */
    [[nodiscard]] const Vector2& direction() const;

    /**
     * Set the direction of the line
     * @param direction The new direction of the line
     */
    void setDirection(Vector2 direction);

    /**
     * Get the point that the line passes through
     * @return The point that the line passes through
     */
    [[nodiscard]] const Vector2& pasingPoint() const;

    /**
     * Set the point that the line passes through
     * @param pasingPoint The new point that the line passes through
     */
    void setPasingPoint(Vector2 pasingPoint);

    /**
     * Check if the line intersects with another line
     * @param other  The other line
     * @return The intersection point if the lines intersect, otherwise std::nullopt
     */
    [[nodiscard]] std::optional<Vector2> intersection(const Line& other) const;

    /**
     * Check if the line intersects with a segment
     * @param segment The segment
     * @return The intersection point if the line intersects with the segment, otherwise
     * std::nullopt
     */
    [[nodiscard]] std::optional<Vector2> intersection(const Segment& segment) const;

    /**
     * Check if the line intersects with a point
     * @param point The point
     * @return True if the line intersects with the point, otherwise false
     */
    [[nodiscard]] bool intersection(const Vector2& point) const;

    /**
     * Check if the line is parallel to another line
     * @param other The other line
     * @return True if the line is parallel to the other line, otherwise false
     */
    [[nodiscard]] bool isParallelTo(const Line& other) const;

    /**
     * Check if a given point is between two lines
     * @param line1 The first line
     * @param point The point
     * @param line2 The second line
     * @return True if the point is between the two lines, otherwise false
     * @pre The lines must be parallel
     */
    static bool isBetween(const Line& line1, Vector2 point, const Line& line2);
};
