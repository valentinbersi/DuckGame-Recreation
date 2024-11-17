#include "IntersectionInfo.h"

#include <utility>

IntersectionInfo::IntersectionInfo(Vector2 bouncePosition, Vector2 pushedPosition,
                                   Vector2 collisionNormal):
        bouncePosition(std::move(bouncePosition)),
        pushedPosition(std::move(pushedPosition)),
        collisionNormal(std::move(collisionNormal)) {}