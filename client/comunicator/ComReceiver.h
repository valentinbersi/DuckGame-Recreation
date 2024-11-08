#pragma once
#include "ActiveSocket.h"
#include "BlockingQueue.h"
#include "ClientRecvProtocol.h"
#include "LibError.h"
#include "GameStatus.h"
#include "Thread.h"
#include "syslog.h"

class CommunicatorReceiver: public Thread {
private:
    ClientRecvProtocol recvProtocol;

    BlockingQueue<GameStatus>& recvQueue;

public:
    explicit CommunicatorReceiver(ActiveSocket& socket,
                                  BlockingQueue<GameStatus>& queue);

    void run() override;

    void stop() override;

    ~CommunicatorReceiver();
};
