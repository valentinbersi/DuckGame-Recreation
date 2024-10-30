#pragma once
#include "Thread.h"
#include "ServerRecvProtocol.h"
#include "BlockingQueue.h"
#include "Message.h"
#include "LobbyResolver.h"
#include "Command.h"
#include <memory>
#include "GameMapMonitor.h"

class Receiver: public Thread{
private:
    ServerRecvProtocol recvProtocol;
    BlockingQueue<std::unique_ptr<Command>>* gameQueue;
    LobbyResolver lobbyResolver; 
    // CommnadFactory factory;
public:
    Receiver(ActiveSocket& socket, BlockingQueue<std::unique_ptr<Command>>* queueRecv,
             std::shared_ptr<BlockingQueue<std::shared_ptr<GameStatus>>> queueSender, GameMapMonitor& monitor);

    virtual void run() override;

    void stop() override;

    ~Receiver();
};


