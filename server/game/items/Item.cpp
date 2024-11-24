#include "Item.h"

#include "Layer.h"

#define INVALID "Invalid ItemID"

Item::Item(const float width, const float height, const ItemID id):
        PhysicsObject(nullptr, {0, 0}, Layer::Item, Layer::Wall | Layer::Spawner, width, height,
                      Gravity::Enabled),
        _id(id) {
    if (id == ItemID::NONE)
        throw std::invalid_argument(INVALID);
}

ItemID Item::id() const noexcept { return _id; }

ItemData Item::status() const { return {_id, shape}; }

Item::~Item() = default;
