#pragma once

#include "ItemData.h"
#include "ItemID.h"
#include "PhysicsObject.h"

class Item final: public PhysicsObject {
    ItemID _id;
    u8 _ammo;  // 0 for non weapons

public:
    Item() = delete;
    Item(const Item& other) = delete;
    Item(Item&& other) noexcept = delete;
    Item& operator=(const Item& other) = delete;
    Item& operator=(Item&& other) noexcept = delete;

    /**
     * Construct a EquippableItem with the given id
     * @param width the width of the item
     * @param height the heigth of the item
     * @param id the id of the item
     */
    Item(float width, float height, ItemID id, u8 ammo);

    /**
     * Get the id of the item
     * @return ItemId related to the Item
     */
    ItemID id() const noexcept;


    /**
     * Get the ammo of the item
     * @return ammoint of ammo
     */
    u8 ammo() const noexcept;

    /**
     * Gives Data related to the Item;
     * @return ItemData related to the Item
     */
    ItemData status() const;

    ~Item() override;
};
