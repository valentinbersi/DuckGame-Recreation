
#include "ItemData.h"

ItemData::ItemData(const ItemID& id, const Vector2& position, float width, float height):
        SizedObjectData(position, width, height), id(id) {}

ItemData::ItemData(const ItemID& id, const Rectangle& rectangle):
        SizedObjectData(rectangle), id(id) {}

ItemData::ItemData(const ItemData& other) = default;

ItemData& ItemData::operator=(const ItemData& other) {
    if (this == &other)
        return *this;

    SizedObjectData::operator=(other);
    id = other.id;
    return *this;
}

ItemData::ItemData(ItemData&& other) noexcept:
        SizedObjectData(std::move(other)), id(other.id) {}

ItemData& ItemData::operator=(ItemData&& other) noexcept {
    if (this == &other)
        return *this;

    SizedObjectData::operator=(std::move(other));
    id = other.id;
    return *this;
}

ItemData::~ItemData() = default;

bool ItemData::operator==(const ItemData& other) const {
    return SizedObjectData::operator==(other) && id == other.id;
}
