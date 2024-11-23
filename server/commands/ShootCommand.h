#pragma once
#include "Command.h"
#include "MessageType.h"
// Not used yet
class ShootCommand: public Command {
private:
    InputAction action;

public:
    ShootCommand(const PlayerID id, InputAction action);
    void execute(GameController& GameController) override;
    ~ShootCommand() = default;
};
