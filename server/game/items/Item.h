#pragma once

#include "ItemID.h"
#include "PhysicsObject.h"

class Item final: public PhysicsObject {
    ItemID _id;

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
    explicit Item(float width, float height, ItemID id);

    /**
     * Get the id of the item
     * @return ItemId related to the Item
     */
    ItemID id() const noexcept;

    ~Item() override;
};
