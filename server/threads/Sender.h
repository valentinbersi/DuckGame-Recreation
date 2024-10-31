#pragma once
#include "ActiveSocket.h"
#include "BlockingQueue.h"
#include "Message.h"
#include "ServerSendProtocol.h"
#include "Thread.h"

class Sender: public Thread {
private:
    ServerSendProtocol sendProtocol;
    std::shared_ptr<BlockingQueue<std::shared_ptr<Message>>>& sendQueue;

public:
    Sender(ActiveSocket& socket,
           std::shared_ptr<BlockingQueue<std::shared_ptr<Message>>>& queue);

    virtual void run() override;

    void stop() override;

    ~Sender();
};
