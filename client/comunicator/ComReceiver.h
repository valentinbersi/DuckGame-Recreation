#pragma once
#include "ActiveSocket.h"
#include "BlockingQueue.h"
#include "ClientRecvProtocol.h"
#include "LibError.h"
#include "ServerMessage.h"
#include "Thread.h"
#include "syslog.h"

class CommunicatorReceiver: public Thread {
private:
    ClientRecvProtocol recvProtocol;

    BlockingQueue<std::unique_ptr<ServerMessage>>& recvQueue;

public:
    explicit CommunicatorReceiver(ActiveSocket& socket,
                                  BlockingQueue<std::unique_ptr<ServerMessage>>& queue);

    void run() override;

    void stop() override;

    ~CommunicatorReceiver();
};
