#pragma once
#include "Command.h"
#include "MessageType.h"

class MovementCommand: public Command {
private:
    InputAction action;

public:
    /**
     * Creates a new MovementCommand
     * @param id The id of the player that executed the command
     * @param action The action that the player executed, in this case
     * movement types
     */
    MovementCommand(const PlayerID id, InputAction action);

    /**
     * Executes the command
     * @param GameController The game controller to obtain player from.
     */
    virtual void execute(GameController& GameController) override;

    /**
     * Destroys the MovementCommand
     */
    ~MovementCommand() override;
};
