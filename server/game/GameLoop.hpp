#pragma once

#include <list>

#include "BlockingQueue.h"
#include "Thread.h"

// Place holder for commands
class Command;
class GameController {};
class GameStatus;

class GameLoop final: public Thread {
    constexpr static std::uint8_t FRAME_TIMES_AMOUNT = 2;

    std::list<std::weak_ptr<BlockingQueue<GameStatus>>> clientQueues{};
    BlockingQueue<Command*> clientCommands;
    std::queue<Command*> currentFrameCommands;
    GameController game;
    std::uint64_t prevTicks;

    /**
     * Calculate the time between the previous frame and the current frame
     * @return the time between the previous frame and the current frame in seconds
     */
    double calculateDeltaTime();

    /**
     * Retrieve all the commands the clients send between the previous frame and the current frame
     */
    void retrieveCurrentFrameCommands();

    /**
     * Process all the commands in the current frame
     */
    void processCurrentFrameCommands();

    /**
     * Broadcast the game status to all the clients
     */
    void broadcastGameStatus();

public:
    /**
     * Construct a gameloop with no players
     */
    GameLoop();

    /**
     * Run the gameloop
     */
    void run() override;

    /**
     * Add a client queue to the list of client queues
     * @param clientID the client ID to add
     * @param clientQueue the client queue to add
     */
    void addClient(std::uint16_t clientID, std::weak_ptr<BlockingQueue<GameStatus>> clientQueue);
};
