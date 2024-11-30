#include "ShotGun.h"
#include "Player.h"
#include "Bullet.h"
#include "GameController.h"

Shotgun::Shotgun(ItemID id, u8 ammo, Vector2 recoil, float minReach, float maxReach,float dispersion, u8 pellets):
        EquippableWeapon(id, ammo, std::move(recoil)),
        minReach(minReach),
        maxReach(maxReach), 
        firing(false), 
        pellets(pellets),
        hasToReload(false),
        randomDistanceGenerator(minReach, maxReach),
        randomDispersionGenerator(-dispersion, dispersion) {}

void Shotgun::generateBullet() {
    const Vector2 direction =
            (parent<Player>()->viewDirection() == DuckData::Direction::Right ? Vector2::RIGHT :
                                                                               Vector2::LEFT)
                    .rotated(randomDispersionGenerator());
    for(u8 i(0); i < pellets; ++i) {

        auto bullet = std::make_unique<Bullet>(direction, randomDistanceGenerator.generateRandomInt());
        bullet->setGlobalPosition(
                parent<Player>()->globalPosition() +
                        (parent<Player>()->viewDirection() == DuckData::Direction::Right ?
                                Vector2::RIGHT * 2 :
                                Vector2::LEFT * 2),
                Force::Yes);

        getRoot<GameController>()->addToLevel("Bullet", std::move(bullet));
    }   
}
    
void Shotgun::actionate() {
    if (firing)
        return;

    if (hasToReload) {
        hasToReload = false;
        return;
    }

    if (fire()){
        generateBullet();
        firing = true;
        hasToReload = true;
    }
}

void Shotgun::deactionate() { firing = false; }

Shotgun::~Shotgun() = default;
