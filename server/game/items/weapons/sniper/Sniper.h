
#include "EquippableWeapon.h"
#include "GameTimer.h"

class Sniper final: public EquippableWeapon {
    float reach;
    bool firing;
    bool reloading;
    GameTimer* timer;
    RandomFloatGenerator randomGenerator;

    /**
     * Sets reloading to false, this function goes
     * pair to a timer.
     */
    void setNotReloading();

    /**
     * Generates a bullet
     */
    void generateBullet();
    
public:
    Sniper() = delete;
    Sniper(const Sniper& other) = delete;
    Sniper(Sniper&& other) noexcept = delete;
    Sniper& operator=(const Sniper& other) = delete;
    Sniper& operator=(Sniper&& other) noexcept = delete;

    /**
     * Creates a new Sniper
     * @param id The id of the weapon
     * @param ammo The ammo of the weapon
     * @param recoil The recoil of the weapon
     * @param reach The reach of the weapon
     * @param dispersion The dispersion of the weapon
     * @param reloadTime The reload time of the weapon
     */
    Sniper(ItemID id, u8 ammo, Vector2 recoil, float reach, float dispersion, float reloadTime);

    /**
     * Actionates the weapon
     */
    void actionate() override;

    /**
     * Deactionates the weapon
     */
    void deactionate() override;

    ~Sniper() override;
};