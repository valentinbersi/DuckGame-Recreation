#pragma once
#include "Command.h"

class ExitCommand: public Command {
public:
    /**
     * Creates a new ExitCommand
     * @param id The id of the player that executed the command
     */
    explicit ExitCommand(const PlayerID id);

    /**
     * Executes the command
     * @param gameController The game controller
     */
    void execute(GameController& gameController) override;

    /**
     * Destroys the command
     */
    ~ExitCommand() override;
};
