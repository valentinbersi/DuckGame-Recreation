#pragma once

#include "Vector2.h"

struct GlobalPhysics {
    constexpr static float gravityScalar = 9.8f;  // cppcheck-suppress unusedStructMember
    static const Vector2 gravity;
};
