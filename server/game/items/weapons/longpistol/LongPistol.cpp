
#include "LongPistol.h"

#include "Bullet.h"
#include "Math.h"
#include "Player.h"

#define AMMO 6

LongPistol::LongPistol(const ItemID id, Vector2 recoil, const float dispersion):
        EquippableWeapon(id, AMMO, std::move(recoil), dispersion) {}

#define BULLET_TILES 20
#define BULLET_SPEED 400
#define BULLET_DAMAGE 10

void LongPistol::actionate() {
    static RandomFloatGenerator randomGenerator(-dispersion, dispersion);

    auto parent = dynamic_cast<Player*>(this->parent());

    if (firing)
        return;

    if (ammo == INeedMoreBullets)
        return fire(Events::NoMoreBullets);

    firing = true;
    --ammo;

    const Vector2 direction =
            parent->direction() == DuckData::Direction::Right ?
                    Vector2::RIGHT.rotated(randomGenerator.generateRandomFloat()) :
                    Vector2::LEFT.rotated(randomGenerator.generateRandomFloat());

    auto bullet = std::make_unique<Bullet>(BULLET_DAMAGE, direction * BULLET_SPEED, BULLET_TILES);
    bullet->setGlobalPosition(parent->globalPosition() +
                              (parent->direction() == DuckData::Direction::Right ?
                                       Vector2::RIGHT * 2 :
                                       Vector2::LEFT * 2));
    getRoot()->addChild("Bullet", std::move(bullet));
    fire<const Vector2&>(Events::Fired, recoil);
}

void LongPistol::deactionate() { firing = false; }

void LongPistol::update([[maybe_unused]] float delta) {}

LongPistol::~LongPistol() = default;

CowboyPistol::CowboyPistol(): LongPistol(ItemID::CowboyPistol, Vector2::ZERO, 0.0) {}

CowboyPistol::~CowboyPistol() = default;

Magnum::Magnum(): LongPistol(ItemID::Magnum, Vector2::RIGHT * 5, Math::toRadians(20)) {}

Magnum::~Magnum() = default;
