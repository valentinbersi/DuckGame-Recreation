#pragma once

#include "Vector2.h"

struct GlobalPhysics {
    constexpr static float gravityScalar = 9.8f;
    static const Vector2 gravity;
};
