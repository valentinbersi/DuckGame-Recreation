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

   /**
     * Create a Game and return the matchID
     * @param matchID the id map to a certain Game
     * @param senderQueue the queue to send messages to the clients
     * @param clientID the id of the client requesting to join the game
     * @param playerCount the number of players that will play the game locally
     * @throws std::out_of_range if the game does not exist
     * @throws NoSpaceLeft if the game is full
     * @throws AlreadyStarted if the game was already started
     * @throws MatchEnded if the game ended
    */ 
    BlockingQueue<std::unique_ptr<Command>>* joinGame(
            u16 matchID, std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue,
            u16 clientId, u8 playerCount);

public:
    struct NoSpaceLeft final: std::logic_error{
        /**
         * @param MatchID the id of the match that was full
         */
        explicit NoSpaceLeft(u16 MatchID);
    };

    struct AlreadyStarted final: std::logic_error{
        /**
         * @param MatchID the id of the match that was already started
         */
        explicit AlreadyStarted(u16 MatchID);
    };

    struct MatchEnded final: std::logic_error{
        /**
         * @param MatchID the id of the match that ended
         */
        explicit MatchEnded(u16 MatchID);
    };

    /**
     * Create a new GameMapMonitor
     */
    GameMapMonitor();

    /**
     * Joins a game Safely
     * @param matchID the id map to a certain Game
     * @param senderQueue the queue to send messages to the clients
     * @param clientID the id of the client requesting to join the game
     * @param playerCount the number of players that will play the game locally
     * @throws std::out_of_range if the game does not exist
     * @throws NoSpaceLeft if the game is full
     * @throws AlreadyStarted if the game was already started
     * @throws MatchEnded if the game ended
    */ 
    BlockingQueue<std::unique_ptr<Command>>* joinGameSafe(
            u16 matchID, std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue,
            u16 clientId, u8 playerCount);

    /**
     * Start the game with the given matchID Safely
     * @param matchID the id of the game to start
     * @return the queue to send commands to the game
     * @throws std::out_of_range if the game does not exist
     * @throws AlreadyStarted if the game was already started
     * @throws MatchEnded if the game ended
     */
    BlockingQueue<std::unique_ptr<Command>>* startGameSafe(u16 matchID);


    /**
     * Create Game and Joins Safely
     * @param senderQueue the queue to send messages to the clients
     * @param clientID the id of the client requesting to join the game
     * @param playerCount the number of players that will play the game locally
     */
    void createGameAndJoinSafe(std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> senderQueue,
            u16 clientId, u8 playerCount);

    /**
     * Get the level data of the game with the given matchID
     */
    ~GameMapMonitor();
};
