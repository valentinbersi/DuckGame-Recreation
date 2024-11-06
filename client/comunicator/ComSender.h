#pragma once

#include "ActiveSocket.h"
#include "BlockingQueue.h"
#include "ClientMessage.h"
#include "ClientSendProtocol.h"
#include "LibError.h"
#include "Thread.h"
#include "syslog.h"


class CommunicatorSender: public Thread {
private:
    ClientSendProtocol sendProtocol;

    BlockingQueue<std::unique_ptr<ClientMessage>>& sendQueue;

public:
    explicit CommunicatorSender(ActiveSocket& socket,
                                BlockingQueue<std::unique_ptr<ClientMessage>>& queue);

    void run() override;

    void stop() override;

    ~CommunicatorSender();
};
