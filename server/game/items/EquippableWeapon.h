#include "GameObject.h"
#include "ItemID.h"
#include "Types.h"

class EquippableWeapon: public GameObject {
protected:
    ItemID id;

public:
    explicit EquippableWeapon(ItemID id);

    ItemID getID() const;

    virtual void shoot() = 0;

    virtual ~EquippableWeapon() = default;
};
