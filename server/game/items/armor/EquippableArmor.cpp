#include "EquippableArmor.h"

#include "Player.h"

EquippableArmor::EquippableArmor(ItemID id, const u8 protection):
        EquippableItem(), protection(protection) {}

void EquippableArmor::actionate() {
    switch (id) {
        case ItemID::Helmet:
            parent<Player>()->equipHelmet(protection);
            break;
        case ItemID::Armor:
            parent<Player>()->equipArmor(protection);
            break;
        default:
            throw std::logic_error("Invalid armor id");
    }
}