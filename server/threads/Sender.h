#pragma once
#include "ServerSendProtocol.h"
#include "BlockingQueue.h"
#include "ActiveSocket.h"
#include "GameStatus.h"
#include "Thread.h"

class Sender: public Thread {
private:
    ServerSendProtocol sendProtocol;
    std::shared_ptr<BlockingQueue<std::shared_ptr<GameStatus>>>& sendQueue;

public:
    Sender(ActiveSocket& socket, std::shared_ptr<BlockingQueue<std::shared_ptr<GameStatus>>>& queue);

    virtual void run() override;

    void stop() override;

    ~Sender();
};
