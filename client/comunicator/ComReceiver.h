#pragma once
#include "ActiveSocket.h"
#include "BlockingQueue.h"
#include "ClientRecvProtocol.h"
#include "GameStatus.h"
#include "Message.h"
#include "LibError.h"
#include "Thread.h"
#include "syslog.h"

class CommunicatorReceiver: public Thread {
private:
    ClientRecvProtocol recvProtocol;

    BlockingQueue<std::unique_ptr<Message>>& recvQueue;

public:
    explicit CommunicatorReceiver(ActiveSocket& socket, BlockingQueue<std::unique_ptr<Message>>& queue);

    virtual void run() override;

    void stop() override;

    ~CommunicatorReceiver();
};
