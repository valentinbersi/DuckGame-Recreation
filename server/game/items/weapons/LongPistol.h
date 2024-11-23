#pragma once

#include "EquippableWeapon.h"
#include "GameTimer.h"

class LongPistol: public EquippableWeapon {
public:
    /**
     * Creates a new LongPistol
     * @param id The id of the weapon
     * @param recoil The recoil of the weapon
     * @param dispersion The dispersion of the weapon
     */
    explicit LongPistol(ItemID id, float recoil, float dispersion);

    //To implement
    float actionate() override;

    //To implement
    void deactionate() override;

    //To implement
    void update(float delta) override;

    virtual ~LongPistol() override;
};

class CowboyPistol: public LongPistol {
public:
    /**
     * Creates a new CowboyPistol
     * @param id The id of the weapon
     */
    explicit CowboyPistol(ItemID id);

    ~CowboyPistol() override;
};

class Magnum: public LongPistol {
public:
    /**
     * Creates a new Magnum
     * @param id The id of the weapon
     */
    explicit Magnum(ItemID id);

    ~Magnum() override;
};
