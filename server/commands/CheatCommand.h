#pragma once
#include "Command.h"
#include "MessageType.h"

class CheatCommand: public Command {
private:
    InputAction cheatCode;

public:
    /**
     * Creates a new CheatCommand
     * @param id The id of the player that executed the command
     * @param cheat The cheat that the player executed.
     */
    CheatCommand(const PlayerID id, InputAction cheat);

    /**
     * Executes the command
     * @param GameController The game controller to obtain player from.
     */
    void execute(GameController& GameController) override;

    /**
     * Destroys the CheatCommand
     */
    ~CheatCommand() override;
};
