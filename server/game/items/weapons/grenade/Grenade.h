#pragma once
#include "PhysicsObject.h"
#include "EquippableWeapon.h"
#include "ItemID.h"

class Grenade : public PhysicsObject{
private:

public:
    Grenade(ItemID id, u8 ammo,float timeToExplode);

    /**
     * Manages the desaceleration needed
     * 
     */
    void update(float delta) override;

    ~Grenade() override;
};
