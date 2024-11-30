
#include "InteractCommand.h"

InteractCommand::InteractCommand(PlayerID id): Command(id) {}

void InteractCommand::execute(GameController& gameController) {
    if (!gameController.roundInProgress()) {
        return;
    }
    gameController.getPlayer(id).interact();
}

InteractCommand::~InteractCommand() = default;
