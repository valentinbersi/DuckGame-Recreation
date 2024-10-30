#pragma once
#include "Thread.h"
#include "BlockingQueue.h"
#include "GameStatus.h"
#include "ActiveSocket.h"
#include "ClientRecvProtocol.h"
#include "LibError.h"
#include "ComSender.h"
#include "syslog.h"

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
