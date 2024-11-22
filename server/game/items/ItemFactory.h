#pragma once

#include <memory>

#include "Item.h"
#include "unordered_map"

class ItemFactory {
    /**
     * HashMap used to create Item
     */
    static std::unordered_map<ItemID, std::function<std::unique_ptr<Item>()>> factory;

public:
    /**
     * Creates Item base on given ItemID, throws exception
     * in case id does not corresponde to any item
     * @param id
     * @return unique pointer to Created Item
     */
    static std::unique_ptr<Item> createItem(const ItemID id);
};
