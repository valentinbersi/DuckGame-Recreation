
#include "MovementCommand.h"
MovementCommand::MovementCommand(PlayerID id, InputAction action): Command(id), action(action) {}

void MovementCommand::execute(GameController& gameController) {

    Player& player = gameController.getPlayer(id);
    switch (action) {
        case InputAction::LEFT_PRESSED:
            player.moveLeft();
            break;
        case InputAction::RIGHT_PRESSED:
            player.moveRight();
            break;

        case InputAction::LEFT_RELEASED:
            player.stopMoveLeft();
            break;

        case InputAction::RIGHT_RELEASED:
            player.stopMoveRight();
            break;

        case InputAction::DOWN_PRESSED:
            player.crouch();
            break;
        
        case InputAction::DOWN_RELEASED:
            player.stopCrouch();
            break;

        default:
            break;
    }
}
