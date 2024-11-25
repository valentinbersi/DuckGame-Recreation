
#include "LongPistol.h"

#define AMMO 6

LongPistol::LongPistol(const ItemID id, Vector2 recoil, const float dispersion):
        EquippableWeapon(id, AMMO, std::move(recoil), dispersion) {}

void LongPistol::actionate() {
    if (!firing) {
        firing = true;
    }
}

void LongPistol::deactionate() {
    firing = false;
}

void LongPistol::update([[maybe_unused]] float delta) {}

LongPistol::~LongPistol() = default;

CowboyPistol::CowboyPistol(): LongPistol(ItemID::CowboyPistol, Vector2::ZERO, 0.0) {}

CowboyPistol::~CowboyPistol() = default;

Magnum::Magnum(): LongPistol(ItemID::Magnum, Vector2::RIGHT, 1.0) {}

Magnum::~Magnum() = default;
