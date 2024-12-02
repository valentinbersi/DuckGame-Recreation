#include "EquippableItem.h"

EquippableItem::EquippableItem(const ItemID id): id_(id) {}

ItemID EquippableItem::id() const { return id_; }

std::list<Segment2D> EquippableItem::status() const { return std::list<Segment2D>(); }

u8 EquippableItem::ammo() const { return 0; }
