#include "GameObject.h"
#include "ItemID.h"
#include "Types.h"

class EquippableWeapon: public GameObject {
protected:
    u8 ammo;
    ItemID id;
    bool firing;
    float recoil;
    float dispersion;

public:
    EquippableWeapon();

    explicit EquippableWeapon(ItemID id, u8 ammo, float recoil, float dispersion);

    ItemID getID() const;

    /**
     * @return the recoil for the weapon to change player velocity.
     */
    virtual float actionate() = 0 ;

    virtual void deactionate() = 0;

    virtual ~EquippableWeapon();
};
