#pragma once
#include "Command.h"

class ExitCommand: public Command {
public:
    ExitCommand(const PlayerID id);
    void execute(GameController& gameController) override;
    ~ExitCommand() = default;
};
