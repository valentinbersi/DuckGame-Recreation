#include <memory>

#include "Command.h"
#include "MessageType.h"
#include "Types.h"

class CommandFactory {
public:
    /**
     * HashMap used to create Commnad
     */
    static HashMap<InputAction, std::function<std::unique_ptr<Command>(PlayerID)>> factory;

public:
    /**
     * Create a Command object
     * @param input corresponding to the usr action or request
     * @return unique pointer to Created Command
     */
    static std::unique_ptr<Command> createCommand(const InputAction input, const PlayerID id);
};
