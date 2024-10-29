#pragma once

#include "ClientSendProtocol.h"
#include "Thread.h"
#include "BlockingQueue.h"
#include "ActiveSocket.h"
#include "ComReceiver.h"
#include "GameStatus.hpp"

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
