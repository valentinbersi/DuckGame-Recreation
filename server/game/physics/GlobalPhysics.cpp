#include "GlobalPhysics.h"

#include "Config.h"

GlobalPhysics::GlobalPhysics(): gravityScalar(Config::Physics::gravity()) {}

GlobalPhysics::~GlobalPhysics() = default;

GlobalPhysics& GlobalPhysics::get() {
    static GlobalPhysics instance;
    return instance;
}

Vector2 GlobalPhysics::gravity() const { return Vector2::DOWN * gravityScalar; }
