#include "EquippableWeapon.h"
#include "GameTimer.h"
class Ak47 final: public EquippableWeapon {
    float reach;
    bool delay;
    u32 bulletsFired;
    RandomFloatGenerator randomDispersionMin;
    RandomFloatGenerator randomDispersionMid;
    RandomFloatGenerator randomDispersionMax;
    GameTimer* timer;

    void onTimeOut();

    Vector2 generateDirection();

    void generateBullet();

public:
    Ak47() = delete;
    Ak47(const Ak47& other) = delete;
    Ak47(Ak47&& other) noexcept = delete;
    Ak47& operator=(const Ak47& other) = delete;
    Ak47& operator=(Ak47&& other) noexcept = delete;

    /**
     * Creates a new Ak47
     * @param id The id of the weapon
     * @param ammo The ammo of the weapon
     * @param recoil The recoil of the weapon
     * @param reach The reach of the weapon
     * @param dispersion The dispersion of the weapon
     */
    Ak47(ItemID id, u8 ammo, Vector2 recoil, float reach, float minDispersion, float midDispersion,
         float maxDispersion, float timeBetweenShots);

    /**
     * Actionates the weapon
     */
    void actionate() override;

    /**
     * Deactionates the weapon
     */
    void deactionate() override;

    ~Ak47() override;
};
