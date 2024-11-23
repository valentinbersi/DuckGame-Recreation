#pragma once
#include "GameController.h"

class Command {
protected:
    const PlayerID id;

public:
    /**
     * Creates a new Command
     * @param id The id of the player that executed the command
     */
    explicit Command(PlayerID id): id(id) {}

    /**
     * Executes the command
     * @param gameController The game controller
     */
    virtual void execute(GameController&) = 0;

    /**
     * Destroys the command
     */
    virtual ~Command() = default;
};
