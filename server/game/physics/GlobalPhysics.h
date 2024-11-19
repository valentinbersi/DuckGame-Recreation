#pragma once

#include "Vector2.h"

struct GlobalPhysics {
    constexpr static float gravityScalar = 2000.0f;
    static const Vector2 gravity;
};
