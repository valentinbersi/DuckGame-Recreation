#pragma once

#include "EquippableWeapon.h"

struct LongPistol: EquippableWeapon {
    LongPistol() = delete;
    LongPistol(const LongPistol& other) = delete;
    LongPistol(LongPistol&& other) noexcept = delete;
    LongPistol& operator=(const LongPistol& other) = delete;
    LongPistol& operator=(LongPistol&& other) noexcept = delete;

    RandomFloatGenerator randomGenerator;

    /**
     * Creates a new LongPistol
     * @param id The id of the weapon
     * @param recoil The recoil of the weapon
     * @param dispersion The dispersion of the weapon
     */
    explicit LongPistol(ItemID id, Vector2 recoil, float dispersion);

    /**
     * Actionates the weapon
     * @return The recoil of the weapon
     */
    void actionate() override;

    /**
     * Deactionates the weapon
     * @return The recoil of the weapon
     */
    void deactionate() override;

    /**
     * Updates the weapon
     * @param delta The time passed since the last update
     */
    void update(float delta) override;

    ~LongPistol() override;
};

class CowboyPistol final: public LongPistol {
public:
    /**
     * Creates a new CowboyPistol
     * @param id The id of the weapon
     */
    explicit CowboyPistol();

    ~CowboyPistol() override;
};

class Magnum final: public LongPistol {
public:
    /**
     * Creates a new Magnum
     * @param id The id of the weapon
     */
    explicit Magnum();

    ~Magnum() override;
};
