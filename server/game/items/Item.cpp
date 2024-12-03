#include "Item.h"

#include "Layer.h"

#define INVALID "Invalid ItemID"

Item::Item(const float width, const float height, const ItemID id, const u8 ammo):
        PhysicsObject({0, 0}, Layer::Item, Layer::Wall | Layer::Spawner, width, height,
                      Gravity::Enabled, Vector2::ZERO, CollisionType::Slide),
        _id(id),
        _ammo(ammo) {
    if (id == ItemID::NONE)
        throw std::invalid_argument(INVALID);
}

ItemID Item::id() const noexcept { return _id; }

u8 Item::ammo() const noexcept { return _ammo; }

ItemData Item::status() const { return {_id, shape}; }

Item::~Item() = default;
