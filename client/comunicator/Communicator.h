#pragma once
#include "Thread.h"
#include "BlockingQueue.h"
#include "ActiveSocket.h"
#include "ComReceiver.h"
#include "ComSender.h"
#include "GameStatus.h"
#include "ClientMessage.h"

#include <iostream>

class Communicator{
private:
    ActiveSocket skt;
    BlockingQueue<ClientMessage> sendQueue;
    BlockingQueue<GameStatus> recvQueue;
    CommunicatorSender sender;
    CommunicatorReceiver receiver;

public:
    explicit Communicator(ActiveSocket&& socket);

    bool trysend(const ClientMessage& Message);

    std::optional<GameStatus> tryrecv();

    ~Communicator();
};
