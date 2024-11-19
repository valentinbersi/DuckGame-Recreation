#pragma once
#include "Command.h"
#include "MessageType.h"

class ShootCommand : public Command {
private:
    InputAction action;
public:
    ShootCommand(const PlayerID id, InputAction action);
    void execute(GameController& GameController) override;
    ~ShootCommand() = default;
};
