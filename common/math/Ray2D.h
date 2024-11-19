#pragma once

#include "Vector2.h"

class Ray2D {
    Vector2 _origin;
    Vector2 _direction;

public:
    /**
     * Construct a ray with the given origin and direction
     * @param origin The origin of the ray
     * @param direction The direction of the ray
     */
    Ray2D(Vector2 origin, Vector2 direction);

    /**
     * Get the origin of the ray
     * @return The origin of the rays
     */
    [[nodiscard]] Vector2 origin() const;

    /**
     * Set the origin of the ray
     * @param origin The new origin of the ray
     */
    void setOrigin(Vector2 origin);

    /**
     * Get the direction of the ray
     * @return The direction of the ray
     */
    [[nodiscard]] Vector2 direction() const;

    /**
     * Set the direction of the ray
     * @param direction The new direction of the ray
     */
    void setDirection(Vector2 direction);
};
