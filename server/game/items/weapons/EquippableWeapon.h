#pragma once

#include "GameObject.h"
#include "ItemID.h"
#include "Types.h"
#include "Vector2.h"

class EquippableWeapon: public GameObject {
protected:
    u8 ammo;
    ItemID id;
    bool firing;
    Vector2 recoil;
    float dispersion;

public:
    constexpr static u8 INeedMoreBullets = 0;

    EquippableWeapon() = delete;
    EquippableWeapon(const EquippableWeapon& other) = delete;
    EquippableWeapon(EquippableWeapon&& other) noexcept = delete;
    EquippableWeapon& operator=(const EquippableWeapon& other) = delete;
    EquippableWeapon& operator=(EquippableWeapon&& other) noexcept = delete;

    /**
     * Creates a new EquippableWeapon
     * @param id The id of the weapon
     * @param ammo The ammo of the weapon
     * @param recoil The recoil of the weapon
     * @param dispersion The dispersion of the weapon
     *
     */
    explicit EquippableWeapon(ItemID id, u8 ammo, Vector2 recoil, float dispersion);

    /**
     * Get the id of the weapon
     * @return The id of the weapon
     */
    ItemID getID() const;

    /**
     * Actionate the weapon
     * @return The recoil of the weapon
     */
    virtual void actionate() = 0;

    /**
     * Actionate the weapon
     * @return The recoil of the weapon
     */
    virtual void deactionate() = 0;

    struct Events {
        constexpr static auto Fired = "Fired";
        constexpr static auto NoMoreBullets = "NoMoreBullets";
    };

    ~EquippableWeapon() override;
};
