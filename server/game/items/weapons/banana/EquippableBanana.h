
#include "EquippableWeapon.h"

class EquipabbleBanana: public EquippableWeapon {
private:
    bool Pressed;

public:

    EquipabbleBanana(ItemID id, u8 ammo);

    /**
     * Throws a banana and decrements ammo.
     */
    void actionate() override;

    /**
     * Checks if there is no more ammo.
     */
    void update(float delta) override;

    /**
     * Set Pression to false.
     */
    void deactionate() override;

    ~EquipabbleBanana() override;

};