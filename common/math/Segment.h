#pragma once

#include <optional>

#include "Vector2.h"

/**
 * A segment in 2D space
 */
class Segment {
    Vector2 _start;
    Vector2 _end;

public:
    Segment() = delete;
    Segment(const Segment& other) = delete;
    Segment(Segment&& other) noexcept = delete;
    Segment& operator=(const Segment& other) = delete;
    Segment& operator=(Segment&& other) noexcept = delete;

    /**
     * Construct a segment with a start and an end
     * @param start The start of the segment
     * @param end The end of the segment
     */
    Segment(Vector2 start, Vector2 end);

    /**
     * Get the start of the segment
     * @return The start of the segment
     */
    [[nodiscard]] const Vector2& start() const;

    /**
     * Set the start of the segment
     * @param start The new start of the segment
     * @return This segment
     */
    Segment& setStart(Vector2 start);

    /**
     * Get the end of the segment
     * @return The end of the segment
     */
    [[nodiscard]] const Vector2& end() const;

    /**
     * Set the end of the segment
     * @param end The new end of the segment
     * @return This segment
     */
    Segment& setEnd(Vector2 end);

    /**
     * Check if a point is lying on this segment
     * @param v The point to check
     * @return True if the point is lying on the segment, false otherwise
     */
    bool isLying(const Vector2& v) const;

    /**
     * Check if this segment intersects with another segment
     * @param segment The other segment
     * @return The intersection point if the segments intersect, std::nullopt otherwise
     */
    [[nodiscard]] std::optional<Vector2> intersects(const Segment& segment) const;
};
