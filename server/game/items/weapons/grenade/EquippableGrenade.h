#pragma once
#include "EquippableItem.h"
#include "GameTimer.h"

class EquippableGrenade : public EquippableItem {
private:
    GameTimer* timer;

    void onTimeout();

public:
    EquippableGrenade(ItemID id, float timeToExplode);

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
