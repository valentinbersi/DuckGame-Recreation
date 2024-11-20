
#include "ExitCommand.h"

ExitCommand::ExitCommand(const PlayerID id): Command(id) {}

void ExitCommand::execute(GameController& gameController) {
    try {
        gameController.removePlayer(id);
    } catch (const GameController::PlayerNotFound& err) {
        // expected
    }
}
