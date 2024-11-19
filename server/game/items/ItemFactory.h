#pragma once
#include "EquippableItem.h"
#include "unordered_map"

class ItemFactory {
private:
    static std::unordered_map<GunID, std::function<std::unique_ptr<EquippableItem>()>> factory;
    static void inicializeFactory();

public:
    static std::unique_ptr<EquippableItem> createItem(GunID id);
};
