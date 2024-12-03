#pragma once

#include <array>

#include "Vector2.h"

class Rectangle;

struct IntersectionInfo {
    Vector2 contactPoint;
    Vector2 contactNormal;
    float contactTime;
    std::array<Rectangle*, 4> contact;

    /**
     * Construct an intersection info with all its fields set to 0
     */
    IntersectionInfo();
};
