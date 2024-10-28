#pragma once
#include "../protocol/ClientSendProtocol.h"
#include "../../common/thread/Thread.h"
#include "../../common/synchronized/BlockingQueue.h"
#include "../../common/socket/ActiveSocket.h"
#include "ComReceiver.h"
#include "../../../common/game/GameStatus.hpp"
#include "../protocol/ClientMessage.h"

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
