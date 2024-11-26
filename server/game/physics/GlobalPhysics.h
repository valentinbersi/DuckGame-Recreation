#pragma once

#include "Vector2.h"

struct GlobalPhysics {
    constexpr static float gravityScalar = 20.0f;  // cppcheck-suppress unusedStructMember
    static const Vector2 gravity;
};
