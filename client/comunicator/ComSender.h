#pragma once

#include "ClientSendProtocol.h"
#include "Thread.h"
#include "BlockingQueue.h"
#include "ActiveSocket.h"
#include "ComReceiver.h"
#include "GameStatus.h"

class CommunicatorSender: public Thread{
private:
    ClientSendProtocol sendProtocol;

    BlockingQueue<Message>& sendQueue;
    
public:
    explicit CommunicatorSender(ActiveSocket& socket, BlockingQueue<Message>& queue);

    virtual void run() override;

    void stop() override;

    ~CommunicatorSender();
};
