#pragma once

#include "GameObject.h"
#include "ItemID.h"
#include "Types.h"
#include "Vector2.h"

class EquippableWeapon: public GameObject {
    ItemID id_;
    u8 ammo_;
    Vector2 recoil;

protected:
    /**
     * Fires the weapon, this means decrementing the ammo. If the ammo is 0, it will fire the
     * NoMoreBullets event, otherwise it will fire the Fired event.
     * @return True if the weapon was fired, false otherwise
     */
    virtual bool fire();

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
     */
    EquippableWeapon(ItemID id, u8 ammo, Vector2 recoil);

    /**
     * Get the id of the weapon
     * @return The id of the weapon
     */
    ItemID id() const;

    /**
     * Actionate the weapon
     */
    virtual void actionate() = 0;

    /**
     * Actionate the weapon
     */
    virtual void deactionate() = 0;

    struct Events {
        constexpr static auto Fired = "Fired";
        constexpr static auto NoMoreBullets = "NoMoreBullets";
    };

    ~EquippableWeapon() override;
};
