
#include "MovementCommand.h"
MovementCommand::MovementCommand(PlayerID id, InputAction action): Command(id), action(action) {}

void MovementCommand::execute(GameController& gameController) {

    Player& player = gameController.getPlayer(id);
    switch (action) {
        case InputAction::LEFT_PRESSED:
            return player.moveLeft();

        case InputAction::RIGHT_PRESSED:
            return player.moveRight();

        case InputAction::LEFT_RELEASED:
            return player.stopMoveLeft();

        case InputAction::RIGHT_RELEASED:
            return player.stopMoveRight();

        case InputAction::DOWN_PRESSED:
            return player.crouch();

        case InputAction::DOWN_RELEASED:
            return player.stopCrouch();

        case InputAction::JUMP_PRESSED:
            return player.jump();

        case InputAction::JUMP_RELEASED:
            return player.stopJump();

        default:
            return;
    }
}

MovementCommand::~MovementCommand() = default;
