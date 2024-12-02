#include "WeaponCheatsCommand.h"

WeaponCheatsCommand::WeaponCheatsCommand(const PlayerID id, InputAction cheat):
        Command(id),
        cheatCode(cheat),
        cheatMap{{InputAction::AK47_CHEAT, ItemID::Ak47},
                 {InputAction::SHOTGUN_CHEAT, ItemID::Shotgun},
                 {InputAction::MAGNUM_CHEAT, ItemID::Magnum},
                 {InputAction::COWBOYPISTOL_CHEAT, ItemID::CowboyPistol},
                 {InputAction::DUELPISTOL_CHEAT, ItemID::DuelPistol},
                 {InputAction::SNIPER_CHEAT, ItemID::Sniper},
                 {InputAction::LASER_RIFLE_CHEAT, ItemID::LaserRifle},
                 {InputAction::PEWPEW_CHEAT, ItemID::PewPewLaser},
                 {InputAction::GRENADE_CHEAT, ItemID::Grenade},
                 {InputAction::BANANA_CHEAT, ItemID::Banana},
                 {InputAction::ARMOR_CHEAT, ItemID::Armor},
                 {InputAction::HELMET_CHEAT, ItemID::Helmet}} {}

void WeaponCheatsCommand::execute(GameController& gameController) {
    if (InputAction::INFINITE_AMMO == cheatCode) {
        gameController.giveFullAmmoToPlayer(id);
        return;
    }
    gameController.giveItemToPlayer(id, cheatMap[cheatCode]);
}

WeaponCheatsCommand::~WeaponCheatsCommand() = default;
