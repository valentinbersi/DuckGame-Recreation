#pragma once
#include "Command.h"

class InteractCommand : public Command {
public:
    /**
     * Construct a new Interact Command object
     * @param id The id of the player that will interact
     */
    InteractCommand(PlayerID id);

    /**
     * Execute the command
     * @param gameController The game controller that gets player in the game
     */
    void execute(GameController& gameController) override;

    /**
     * Destroy the Interact Command object
     */
    ~InteractCommand() override;
};
