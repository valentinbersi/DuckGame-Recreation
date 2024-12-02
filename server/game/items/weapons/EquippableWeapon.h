#pragma once

#include "EquippableItem.h"
#include "ItemID.h"
#include "Types.h"
#include "Vector2.h"

class EquippableWeapon: public EquippableItem {
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
     * @return the ammo associated
     */
    u8 ammo() const override;

    /**
     * Set the ammo of the weapon
     * @param ammo The ammo to set
     */
    void setAmmo(const u8 ammo) override;
    
    struct Events {
        constexpr static auto Fired = "Fired";
        constexpr static auto NoMoreBullets = "NoMoreBullets";
    };

    ~EquippableWeapon() override;
};
