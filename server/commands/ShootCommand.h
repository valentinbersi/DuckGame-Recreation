#pragma once
#include "Command.h"
#include "MessageType.h"
// Not used yet
class ShootCommand: public Command {
private:
    InputAction action;

public:
    /**
     * Creates a new ShootCommand
     * @param id The id of the player that executed the command
     * @param action The action that the player executed, in this case
     * shoot pressed or shoot released.
     */
    ShootCommand(const PlayerID id, InputAction action);

    /**
     * Executes the command
     * @param GameController The game controller to obtain player from.
     */
    void execute(GameController& GameController) override;

    /**
     * Destroys the ShootCommand
     */
    ~ShootCommand() override;
};
