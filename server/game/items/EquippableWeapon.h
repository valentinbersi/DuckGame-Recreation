#include "GunID.h"
#include "GameObject.h"
#include "Types.h"

class EquippableWeapon: public GameObject{
protected:
    GunID id;

public:
    EquippableWeapon(GunID id);

    GunID getID() const;

    virtual void shoot() = 0;

    virtual ~EquippableWeapon() = default;
};
