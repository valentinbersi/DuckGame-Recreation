#include "NextRoundCommand.h"

NextRoundCommand::NextRoundCommand(PlayerID id): Command(id) {}

void NextRoundCommand::execute(GameController& gameController) {
    if(!gameController.roundInProgress()){
        gameController.startNewRound();
    } 
}

NextRoundCommand::~NextRoundCommand() = default;
