#pragma once

#include <memory>

#include "EquippableItem.h"
#include "unordered_map"

class EquippableItemFactory {
    /**
     * HashMap used to create EquippableItem
     */
    static std::unordered_map<ItemID, std::function<std::unique_ptr<EquippableItem>(u8)>> factory;

public:
    /**
     * Creates Equippable item base on given ItemID, throws exception
     * in case id does not corresponde to any Equippable item
     * @param id
     * @return unique pointer to Created Equippable Item
     */
    static std::unique_ptr<EquippableItem> createEquippableItem(const ItemID id, u8 ammo);
};
