#pragma once

#include "ClientSendProtocol.h"
#include "Thread.h"
#include "BlockingQueue.h"
#include "ActiveSocket.h"
#include "ComReceiver.h"
#include "GameStatus.hpp"
#include "ClientSendProtocol.h"

class CommunicatorSender: public Thread{
private:
    ClientSendProtocol sendProtocol;

    BlockingQueue<ClientMessage>& sendQueue;
    
public:
    CommunicatorSender(ActiveSocket& socket, BlockingQueue<ClientMessage>& queue);

    void run() override;

    void stop() override;

    ~CommunicatorSender();
};
