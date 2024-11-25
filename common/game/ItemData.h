#pragma once
#include "ItemID.h"
#include "SizedObjectData.h"

struct ItemData: public SizedObjectData {
    ItemID id;

    ItemData() = delete;
    ItemData(const ItemData& other);
    ItemData& operator=(const ItemData& other);
    ItemData(ItemData&& other) noexcept;
    ItemData& operator=(ItemData&& other) noexcept;
    ~ItemData() override;

    /**
     * Construct a item data with the given id, position and rectangle
     * @param id the item id
     * @param position the position
     * @param width the width
     * @param height the height
     */
    ItemData(const ItemID& id, const Vector2& position, float width, float height);

    /**
     * Construct a item data with the given id and rectangle
     * @param id the item id
     * @param rectangle the rectangle
     */
    ItemData(const ItemID& id, const Rectangle& rectangle);

    /**
     * Check if this item data is equal aproximatly to the other item data
     * @param other the other item data
     * @return true if the item data is equal aproximatly to the other item data
     */
    bool operator==(const ItemData& other) const;
};
