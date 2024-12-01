#pragma once

#include "GameObject.h"
#include "ItemID.h"

class EquippableItem: public GameObject {
    ItemID id_;

public:
    EquippableItem() = delete;
    EquippableItem(const EquippableItem& other) = delete;
    EquippableItem(EquippableItem&& other) noexcept = delete;
    EquippableItem& operator=(const EquippableItem& other) = delete;
    EquippableItem& operator=(EquippableItem&& other) noexcept = delete;
    ~EquippableItem() override = default;

    /**
     * Creates a new EquippableItem
     * @param id The id of the item
     */
    explicit EquippableItem(ItemID id);

    /**
     * To override, returns cero if not
     * @return return cero always
     */
    virtual u8 ammo() const;

    /**
     * Get the id of the item
     * @return The id of the item
     */
    ItemID id() const;

    /**
     * Actionate the item
     */
    virtual void actionate() = 0;

    /**
     * Deactionate the item
     */
    virtual void deactionate() = 0;
};
