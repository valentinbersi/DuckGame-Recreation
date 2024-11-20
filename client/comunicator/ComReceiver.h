#pragma once
#include "ActiveSocket.h"
#include "BlockingQueue.h"
#include "ClientRecvProtocol.h"
#include "GameStatus.h"
#include "LibError.h"
#include "Thread.h"
#include "syslog.h"

class CommunicatorReceiver: public Thread {
private:
    ClientRecvProtocol recvProtocol;

    BlockingQueue<ReplyMessage>& recvQueueLobby;

    BlockingQueue<GameStatus>& recvQueueGame;

public:
    explicit CommunicatorReceiver(ActiveSocket& socket, BlockingQueue<ReplyMessage>& queueLobby,
                                  BlockingQueue<GameStatus>& queueGame);

    void run() override;

    void stop() override;

    ~CommunicatorReceiver();
};
