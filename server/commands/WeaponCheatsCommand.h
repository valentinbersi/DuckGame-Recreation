#pragma once
#include "Command.h"
#include "ItemID.h"
#include "MessageType.h"
#include "Types.h"

class WeaponCheatsCommand: public Command {
private:
    InputAction cheatCode;
    HashMap<InputAction, ItemID> cheatMap;

public:
    /**
     * Creates a new WeaponCheatsCommand
     * @param id The id of the player that executed the command
     * @param cheat The cheat that the player executed. In this case, the weapon cheat.
     */
    WeaponCheatsCommand(const PlayerID id, InputAction cheat);

    /**
     * Executes the command
     * @param gameController The game controller to obtain player from.
     */
    void execute(GameController& gameController) override;

    /**
     * Destroys the WeaponCheatsCommand
     */
    ~WeaponCheatsCommand() override;
};
