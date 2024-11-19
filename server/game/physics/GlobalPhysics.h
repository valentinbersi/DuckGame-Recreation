#pragma once

#include "Vector2.h"

struct GlobalPhysics {
    constexpr static float gravityScalar = 2000.0f;  // cppcheck-suppress unusedStructMember
    static const Vector2 gravity;
};
