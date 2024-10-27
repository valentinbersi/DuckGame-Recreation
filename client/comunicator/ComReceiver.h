#pragma once
#include "Thread.h"
#include "ClientRecvProtocol.h"
#include "BlockingQueue.h"
#include "GameStatus.hpp"

class CommunicatorReceiver: public Thread{
private:
    ClientRecvProtocol recvProtocol;

    BlockingQueue<GameStatus>& recvQueue;
    
public:
    explicit CommunicatorReceiver(ActiveSocket& socket, BlockingQueue<GameStatus>& queue);

    virtual void run() override;

    void stop() override;

    ~CommunicatorReceiver();
};
