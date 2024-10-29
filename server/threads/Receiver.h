#pragma once
#include "Thread.h"
#include "ServerRecvProtocol.h"
#include "BlockingQueue.h"
#include "ClientMessage.h"
#include "Command.h"
#include <memory>

class Receiver: public Thread{
private:
    ServerRecvProtocol recvProtocol;
    BlockingQueue<std::unique_ptr<Command>>* gameQueue;
    // CommnadFactory factory;
public:
    Receiver(ActiveSocket& socket, BlockingQueue<std::unique_ptr<Command>>* queue);

    virtual void run() override;

    void stop() override;

    ~Receiver();
};


