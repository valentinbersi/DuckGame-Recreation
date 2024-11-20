#pragma once

#include <map>
#include <memory>
#include <queue>
#include <vector>

#include "BlockingQueue.h"
#include "Command.h"
#include "GameController.h"
#include "LevelData.h"
#include "ServerMessage.h"
#include "Thread.h"
#include "Timer.h"

class GameLoop final: public Thread {
    constexpr static std::uint8_t FRAME_TIMES_AMOUNT = 2;

    std::vector<LevelData> levels;
    std::map<PlayerID, std::weak_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>>>
            clientQueuesMap{};
    BlockingQueue<std::unique_ptr<Command>> clientCommands;
    std::queue<std::unique_ptr<Command>> currentFrameCommands;
    GameController game;
    Timer timer;

    /**
     * Retrieve all the commands the clients send between the previous frame and the current frame
     */
    void retrieveCurrentFrameCommands();

    /**
     * Process all the commands in the current frame
     */
    void processCurrentFrameCommands();

    /**
     * Broadcast a message to all the clients
     * @param message the std::shared_ptr<Servermessage> to broadcast
     */
    void broadcast(std::shared_ptr<ServerMessage> message);

    /**
     * Check if a clientQueue should be maped.
     * @param
     */
    bool shouldAddQueue(const u16 clientID);

public:
    /**
     * Construct a gameloop with no players
     */
    explicit GameLoop(std::vector<LevelData>& levels);

    /**
     * Run the gameloop
     */
    void run() override;

    void stop() override;

    /**
     * Add a client queue to the list of client queues
     * @param clientID the id of the client to add
     * @param clientQueue the queue of the client to add
     */
    void addClient(u16 clientID,
                   std::weak_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> clientQueue);

    /**
     * @return the pointer to the gameloop Queue.
     */
    BlockingQueue<std::unique_ptr<Command>>* getQueue();
};
