#include "EquippableWeapon.h"

#include "Player.h"

void EquippableWeapon::fire() {
    if (ammo_ == INeedMoreBullets)
        return Subject::fire(Events::NoMoreBullets);

    --ammo_;
    Subject::fire<const Vector2&>(Events::Fired, recoil);
}

EquippableWeapon::EquippableWeapon(const ItemID id, const u8 ammo, Vector2 recoil):
        id_(id), ammo_(ammo), recoil(std::move(recoil)) {
    registerEvent<const Vector2&>(Events::Fired);
    registerEvent(Events::NoMoreBullets);
}

ItemID EquippableWeapon::id() const { return id_; }

EquippableWeapon::~EquippableWeapon() = default;
