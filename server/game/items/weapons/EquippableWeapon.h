#pragma once

#include "GameObject.h"
#include "ItemID.h"
#include "Types.h"

class EquippableWeapon: public GameObject {
protected:
    u8 ammo;
    ItemID id;
    bool firing;
    float recoil;
    float dispersion;

public:
    /**
     * Creates a new EquippableWeapon
     * @param id The id of the weapon
     * @param ammo The ammo of the weapon
     * @param recoil The recoil of the weapon
     * @param dispersion The dispersion of the weapon
     *
     */
    explicit EquippableWeapon(ItemID id, u8 ammo, float recoil, float dispersion);

    /**
     * Get the id of the weapon
     * @return The id of the weapon
     */
    ItemID getID() const;


    virtual float actionate() = 0;

    virtual void deactionate() = 0;

    virtual ~EquippableWeapon();
};
