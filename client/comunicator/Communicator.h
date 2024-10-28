#pragma once
#include "../../common/thread/Thread.h"
#include "../../common/synchronized/BlockingQueue.h"
#include "../../common/socket/ActiveSocket.h"
#include "ComReceiver.h"
#include "ComSender.h"
#include "../../../common/game/GameStatus.hpp"
#include "../protocol/ClientMessage.h"

#include <iostream>

class Communicator{
private:
    ActiveSocket skt;
    BlockingQueue<ClientMessage> sendQueue;
    BlockingQueue<GameStatus> recvQueue;
    CommunicatorSender sender;
    CommunicatorReceiver receiver;

public:
    Communicator(ActiveSocket&& socket);

    bool trysend(ClientMessage& Message);

    std::optional<GameStatus> tryrecv();

    ~Communicator();
};
