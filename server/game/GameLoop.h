#pragma once

#include <list>

#include "BlockingQueue.h"
#include "GameController.h"
#include "GameStatus.h"
#include "Thread.h"

class Command;

class GameLoop final: public Thread {
    constexpr static std::uint8_t FRAME_TIMES_AMOUNT = 2;

    std::list<std::weak_ptr<BlockingQueue<std::shared_ptr<GameStatus>>>> clientQueues{};
    BlockingQueue<std::unique_ptr<Command>> clientCommands;
    std::queue<std::unique_ptr<Command>> currentFrameCommands;
    GameController game;
    std::uint64_t prevTicks;

    /**
     * Calculate the time between the previous frame and the current frame
     * @return the time between the previous frame and the current frame in seconds
     */
    float calculateDeltaTime();

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
     * @param clientID the id of the client to add
     * @param clientQueue the queue of the client to add
     */
    void addClient(u16 clientID,
                   std::weak_ptr<BlockingQueue<std::shared_ptr<GameStatus>>> clientQueue);

    /**
     * @return the pointer to the gameloop Queue.
     */
    BlockingQueue<std::unique_ptr<Command>>* getQueue();
};
