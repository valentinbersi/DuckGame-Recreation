#include "Command.h"

class NextRoundCommand : public Command { 
public:
    /**
     * Creates a new NextRoundCommand
     * @param id The id of the player that executed the command
     */
    explicit NextRoundCommand(PlayerID id);

    /**
     * Executes the command
     * @param gameController The game controller used
     */
    void execute(GameController& gameController) override;

    /**
     * Destroys the command
     */
    ~NextRoundCommand() override;
};
