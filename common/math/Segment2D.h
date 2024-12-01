#pragma once

#include <optional>

#include "Vector2.h"

class Segment2D {
    Vector2 start_;
    Vector2 end_;

public:
    /**
     * Create a new RayCast2D object
     * @param begin The beginning of the ray
     * @param end The end of the ray
     */
    Segment2D(Vector2 begin, Vector2 end);

    /**
     * Get the start of the ray
     * @return The start of the ray
     */
    Vector2 start() const;

    /**
     * Get the end of the ray
     * @return The end of the ray
     */
    Vector2 end() const;

    /**
     * Get the intersection point between this ray and another
     * @param other The other ray
     * @return The intersection point
     */
    std::optional<Vector2> intersects(const Segment2D& other) const;
};
