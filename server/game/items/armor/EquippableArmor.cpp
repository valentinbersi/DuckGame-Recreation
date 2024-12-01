#include "EquippableArmor.h"

#include "Player.h"

EquippableArmor::EquippableArmor(ItemID id, const u8 protection):
        EquippableItem(id), protection(protection) {}

void EquippableArmor::actionate() {
    bool wasRemoved = false;
    switch (id()) {
        case ItemID::Helmet:
            wasRemoved = parent<Player>()->equipHelmet(protection);
            break;
        case ItemID::Armor:
            wasRemoved = parent<Player>()->equipArmor(protection);
            break;
        default:
            throw std::logic_error("Invalid armor id");
    }
    if (wasRemoved)
        parent()->removeChild(this);
}

// Just here for herency
void EquippableArmor::deactionate() {}
