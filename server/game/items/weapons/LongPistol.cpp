
#include "LongPistol.h"

#define AMMO 6

LongPistol::LongPistol(ItemID id, float recoil, float dispersion): 
    EquippableWeapon(id, AMMO, recoil, dispersion) {}

float LongPistol::actionate() {
    if (!firing){
        firing = true;

        getRoot() -> addChild("Bullet", std::make_unique<Bullet>(globalPosition(), globalDirection(), id));
        return recoil;
    }
    return 0.0; // Se retorna no recoil porque la tecla sigue presionada.
}

void LongPistol::deactionate(){
    firing = false;
}

void LongPistol::update(float delta) {
   ;
}

LongPistol::~LongPistol() = default;


CowboyPistol::CowboyPistol(ItemID id): LongPistol(id, 0.0, 0.0) {}

CowboyPistol::~CowboyPistol() = default;


Magnum::Magnum(ItemID id): LongPistol(id, 1.0, 1.0) {}

Magnum::~Magnum() = default;
