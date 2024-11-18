#pragma once
#include "Command.h"
#include "MessageType.h"

class MovementCommand: public Command {
private:
    InputAction action;

public:
    MovementCommand(const PlayerID id, InputAction action);
    virtual void execute(GameController& GameController) override;
    ~MovementCommand() = default;
};
