#pragma once

#include <Vector2.h>

struct IntersectionInfo {
    Vector2 bouncePosition;   // The position from where the object should bounce
    Vector2 pushedPosition;   // The position where the object was pushed by the collided object
    Vector2 collisionNormal;  // The normal of the surface the object collided with

    IntersectionInfo(Vector2 bouncePosition, Vector2 pushedPosition, Vector2 collisionNormal);
};
