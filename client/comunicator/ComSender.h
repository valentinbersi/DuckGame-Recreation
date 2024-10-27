#pragma once
#include "Thread.h"
#include "BlockingQueue.h"
#include "ClientSendProtocol.h"
#include "ClientMessage.h"

class CommunicatorSender: public Thread{
private:
    ClientSendProtocol sendProtocol;

    BlockingQueue<ClientMessage>& sendQueue;
    
public:
    explicit CommunicatorSender(ActiveSocket& socket, BlockingQueue<ClientMessage>& queue);

    virtual void run() override;

    void stop() override;

    ~CommunicatorSender();
};
