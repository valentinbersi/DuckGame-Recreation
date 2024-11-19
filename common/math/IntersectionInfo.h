#pragma once

#include "Vector2.h"

struct IntersectionInfo {
    Vector2 contactPoint;
    Vector2 contactNormal;
    float tHitNear;  // cppcheck-suppress unusedStructMember
};
