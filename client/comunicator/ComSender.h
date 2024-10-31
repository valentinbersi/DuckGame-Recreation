#pragma once

#include "ActiveSocket.h"
#include "BlockingQueue.h"
#include "ClientSendProtocol.h"
#include "ComReceiver.h"
#include "GameStatus.h"
#include "Message.h"
#include "Thread.h"

class CommunicatorSender: public Thread {
private:
    ClientSendProtocol sendProtocol;

    BlockingQueue<std::unique_ptr<Message>>& sendQueue;

public:
    explicit CommunicatorSender(ActiveSocket& socket, BlockingQueue<std::unique_ptr<Message>>& queue);

    virtual void run() override;

    void stop() override;

    ~CommunicatorSender();
};
