#include "GameObject.h"
#include "GunID.h"
#include "Types.h"

class EquippableWeapon: public GameObject {
protected:
    GunID id;

public:
    explicit EquippableWeapon(GunID id);

    GunID getID() const;

    virtual void shoot() = 0;

    virtual ~EquippableWeapon() = default;
};
