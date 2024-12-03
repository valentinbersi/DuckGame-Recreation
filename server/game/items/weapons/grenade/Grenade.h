#pragma once
#include "PhysicsObject.h"
#include "EquippableWeapon.h"
#include "ItemID.h"

class Grenade : public PhysicsObject{
private:

public:
    Grenade(ItemID id, const Vector2 position, float timeToExplode);

    /**
     * Manages the desaceleration needed
     * 
     */
    void update(float delta) override;

    ~Grenade() override;
};
