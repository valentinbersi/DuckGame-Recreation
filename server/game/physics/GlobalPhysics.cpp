#include "GlobalPhysics.h"

const Vector2 GlobalPhysics::gravity(initializeGravity());

Vector2 GlobalPhysics::initializeGravity() noexcept { return Vector2::DOWN * gravityScalar; }