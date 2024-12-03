#pragma once
#include "EquippableWeapon.h"
#include "GameTimer.h"

class EquippableGrenade : public EquippableWeapon {
private:
    GameTimer* timer;

    void onTimeout();

public:
    EquippableGrenade(ItemID id, u8 ammo,float timeToExplode);

    /**
     * Activates the grenade counter or throws it
     * if it wa already activated
     */
    void actionate() override;

    /**
     *  Does nothing
     */
    void deactionate() override;

    ~EquippableGrenade() override;
};
