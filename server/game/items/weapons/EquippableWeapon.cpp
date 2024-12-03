#include "EquippableWeapon.h"

#include <utility>

#include "Player.h"

bool EquippableWeapon::fire() {
    if (ammo_ == INeedMoreBullets) {
        Subject::fire(Events::NoMoreBullets);
        return false;
    }

    --ammo_;
    Subject::fire<const Vector2&>(Events::Fired, recoil);
    return true;
}

EquippableWeapon::EquippableWeapon(const ItemID id, const u8 ammo, Vector2 recoil):
        EquippableItem(id), recoil(std::move(recoil)), ammo_(ammo) {
    registerEvent<const Vector2&>(Events::Fired);
    registerEvent(Events::NoMoreBullets);
}

u8 EquippableWeapon::ammo() const { return ammo_; }

void EquippableWeapon::setAmmo(const u8 ammo) { ammo_ = ammo; }

EquippableWeapon::~EquippableWeapon() = default;
