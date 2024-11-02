#pragma once
#include "ActiveSocket.h"
#include "BlockingQueue.h"
#include "ServerMessage.h"
#include "ServerSendProtocol.h"
#include "Thread.h"

class Sender: public Thread {
private:
    ServerSendProtocol sendProtocol;
    std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>>& sendQueue;

public:
    Sender(ActiveSocket& socket,
           std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>>& queue);

    void run() override;

    void stop() override;

    ~Sender();
};
