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
        id_(id), ammo_(ammo), recoil(std::move(recoil)) {
    registerEvent<const Vector2&>(Events::Fired);
    registerEvent(Events::NoMoreBullets);
}

ItemID EquippableWeapon::id() const { return id_; }

EquippableWeapon::~EquippableWeapon() = default;
