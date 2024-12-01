#include "EquippableItem.h"

EquippableItem::EquippableItem(const ItemID id): id_(id) {}

ItemID EquippableItem::id() const { return id_; }

u8 EquippableItem::ammo() const { return 0; }
