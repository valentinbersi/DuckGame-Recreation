
#include "EquippableBanana.h"
#include "Player.h"
#include "GameController.h"

EquipabbleBanana::EquipabbleBanana(ItemID id, u8 ammo): 
                    EquippableWeapon(id, ammo, Vector2::ZERO),
                    Pressed(false){}


void EquipabbleBanana::actionate() {
    if (Pressed) return;
    Pressed = true;
    Vector2 direction = parent<Player>()->aimingDirection();
    Vector2 inicialPosition = parent<Player>()->globalPosition();
    getRoot<GameController>()->addToLevel("Item", std::make_unique<Banana>(ItemID::Banana, inicialPosition, direction));
    --ammo_; 
}

void EquipabbleBanana::update(float delta) {
    if (ammo_ == INeedMoreBullets) {
        parent()->removeChild(this);
    }
}

void EquipabbleBanana::deactionate() { Pressed = false; }

EquipabbleBanana::~EquipabbleBanana() = default;
