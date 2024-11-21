#include "GameObject.h"
#include "ItemID.h"
#include "Types.h"

class EquippableWeapon: public GameObject {
protected:
    u8 ammo;
    ItemID id;

public:
    explicit EquippableWeapon(ItemID id);

    ItemID getID() const;

    virtual void actionate() = 0;

    virtual void deactionate() = 0;

    virtual ~EquippableWeapon();
};
