#include "CheatCommand.h"

CheatCommand::CheatCommand(const PlayerID id, InputAction cheat): Command(id), cheatCode(cheat) {}

void CheatCommand::execute(GameController& gameController) {
    switch (cheatCode) {
        case InputAction::END_ROUND_CHEAT:
            return gameController.endRound();
        case InputAction::END_GAME_CHEAT:
            return gameController.endGame();
        default:
            return;
    }
}

CheatCommand::~CheatCommand() = default;
