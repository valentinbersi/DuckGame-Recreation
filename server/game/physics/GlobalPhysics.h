#pragma once

#include "Vector2.h"

struct GlobalPhysics {
    constexpr static float gravityScalar = 9.8f;
    static const Vector2 gravity;

private:
    /**
     * Get the gravity's value
     * @return the gravity's value
     */
    static Vector2 initializeGravity() noexcept;
};
