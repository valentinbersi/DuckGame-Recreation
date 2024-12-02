#pragma once

#include <list>

#include "GameObject.h"
#include "ItemID.h"
#include "Segment2D.h"

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
     * To override, does nothing on 
     * this class, to implement
     */
    virtual void setAmmo(const u8 ammo);

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

    /**
     * Get the status og the bullets been fired on this frame.
     * Only relevant for Shootable Weapons.
     * @return The segment representing the trayectory of the bullets
     */
    virtual std::list<Segment2D> status() const;
};
