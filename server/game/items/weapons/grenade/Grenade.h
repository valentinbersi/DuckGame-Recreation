#pragma once
#include "EquippableWeapon.h"
#include "ItemID.h"
#include "Item.h"
#include "GameTimer.h"

class Grenade: public Item {
private:
    GameTimer* timer;
    bool hasExploded;

    /**
     * Handles the timer ending event.
     */
    void onTimeout();

public:
    Grenade(ItemID id, const Vector2 position, const Vector2 direction, float timeToExplode);

    /**
     * Manages the desaceleration needed 
     * and explosion of the grenade
     */
    void update(float delta) override;

    ~Grenade() override;
};
