#include "GlobalPhysics.h"

#include "Config.h"

const float GlobalPhysics::gravityScalar(Config::Physics::gravity());

const Vector2 GlobalPhysics::gravity(Vector2(0, 1) * gravityScalar);
