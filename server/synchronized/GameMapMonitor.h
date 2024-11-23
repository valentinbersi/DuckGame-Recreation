#pragma once
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>

#include "GameLoop.h"
#include "LevelData.h"
#include "RandomGenerator.h"
#include "ServerMessage.h"
#include "Types.h"

class GameMapMonitor {
private:
    std::mutex mutex;
    std::unordered_map<u16, std::unique_ptr<GameLoop>> gameMap;
    std::vector<LevelData> levels;
    static RandomIntGenerator randomGenerator;

public:
    /**
     * Create a new GameMapMonitor
     */
    GameMapMonitor();

    /**
     * Create a Game and return the matchID
     * @param matchID the id map to a certain Game
     * @param senderQueue the queue to send messages to the clients
     * @param clientID the id of the client requesting to join the game
     * @param playerCount the number of players that will play the game locally
     * @return the queue to send commands to the game
     */
    BlockingQueue<std::unique_ptr<Command>>* joinGameIfCreated(
            u16 matchID, std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue,
            u16 clientId, u8 playerCount);

    /**
     * Start the game with the given matchID
     * @param matchID the id of the game to start
     * @return the queue to send commands to the game
     */
    BlockingQueue<std::unique_ptr<Command>>* startGameIfCreated(u16 matchID);

    /**
     * Create a new game and return the matchID
     * @return the matchID of the new game
     */
    u16 creatGameSafe();

    /**
     * Get the level data of the game with the given matchID
     */
    ~GameMapMonitor();
};
