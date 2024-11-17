#pragma once
#include "GunID.cpp"
#include "PhysicsObject.h"


class Weapon: public PhysicsObject {
private:
    GunID gunID;

public:
    Weapon(GunID id, GameObject* parent, Vector2 position, const float rotation,
           std::unique_ptr<Shape2D> shape, Vector2 initialVelocity);

    ~Weapon();
};
