#pragma once

#include "ItemID.h"
#include "PhysicsObject.h"


class EquippableItem final: public PhysicsObject {
    ItemID gunID;

public:
    EquippableItem(ItemID);

    ~EquippableItem();
};
