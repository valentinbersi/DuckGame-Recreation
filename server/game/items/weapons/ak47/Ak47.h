#pragma once

#include "CollisionObject.h"
#include "GameTimer.h"
#include "ShootableGun.h"

class Ak47 final: public ShootableGun {
    float reach;
    bool delay;
    u32 bulletsFired;
    bool fireNextFrame;
    RayCast* bullet;
    RandomFloatGenerator randomDispersionMin;
    RandomFloatGenerator randomDispersionMid;
    RandomFloatGenerator randomDispersionMax;
    GameTimer* timer;

    void onTimeOut();

    Vector2 generateDirection();

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
     * @param minDispersion The minimum dispersion of the weapon
     * @param midDispersion The medium dispersion of the weapon
     * @param maxDispersion The maximum dispersion of the weapon
     * @param timeBetweenShots  The time between shots of the weapon
     */
    Ak47(ItemID id, u8 ammo, Vector2 recoil, float reach, float minDispersion, float midDispersion,
         float maxDispersion, float timeBetweenShots);

    /**
     * Updates the weapon
     * @param delta The time passed since the last update
     */
    void update(float delta) override;

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
