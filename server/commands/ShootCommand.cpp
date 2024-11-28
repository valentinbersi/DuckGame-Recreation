#include "ShootCommand.h"

ShootCommand::ShootCommand(const PlayerID id, InputAction action): Command(id), action(action) {}

void ShootCommand::execute(GameController& gameController) {
    if(!gameController.roundInProgress()){
        return;
    }
    Player& player = gameController.getPlayer(id);
    switch (id) {
        case InputAction::SHOOT_PRESSED:
            return player.shoot();
        case InputAction::SHOOT_RELEASED:
            return player.stopShoot();
        default:
            return;
    }
}

ShootCommand::~ShootCommand() = default;
