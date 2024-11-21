#include "EquippableWeapon.h"
#include "GameTimer.h"

class LongPistol: public EquippableWeapon {
protected:
    float recoil;
    float dispersion;

public:
    explicit LongPistol(ItemID id, float recoil, float dispersion);

    void actionate() override;

    void deactionate() override;

    ~LongPistol() override;
}

