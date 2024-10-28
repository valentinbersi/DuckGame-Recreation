#pragma once
#include "../../common/thread/Thread.h"
#include "../../common/synchronized/BlockingQueue.h"
#include "../../common/game/GameStatus.hpp"
#include "../../common/socket/ActiveSocket.h"
#include "../protocol/ClientRecvProtocol.h"
#include "../../common/exceptions/LibError.h"
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
