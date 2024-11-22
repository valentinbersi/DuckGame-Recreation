#pragma once

#include "EquippableWeapon.h"
#include "GameTimer.h"

class LongPistol: public EquippableWeapon {
public:
    explicit LongPistol(ItemID id, float recoil, float dispersion);

    float actionate() override;

    void deactionate() override;

    void update(float delta) override;

    virtual ~LongPistol() override;
};

class CowboyPistol: public LongPistol {
public:
    explicit CowboyPistol(ItemID id);

    ~CowboyPistol() override;
};

class Magnum: public LongPistol {
public:
    explicit Magnum(ItemID id);

    ~Magnum() override;
};
