#pragma once

#include "EquippableItem.h"

class EquippableArmor final: public EquippableItem {
    u8 protection;

public:
    /**
     * Construct an EquippableArmor
     * @param id the item id
     * @param protection the number of shoots the armor can resist
     */
    EquippableArmor(ItemID id, u8 protection);

    /**
     * Equip the armor
     */
    void actionate() override;

    /**
     * Does nothing on armor
     */
    void deactionate() override;
};
