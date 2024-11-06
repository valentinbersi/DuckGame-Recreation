#pragma once
#include "Command.h"
#include "MessageType.h"

class MovementCommand: public Command {
private:
    PlayerID id;
    InputAction action;

public:
    MovementCommand(PlayerID id, InputAction action);
    virtual void execute(GameController& GameController) override;
    ~MovementCommand() = default;
};
