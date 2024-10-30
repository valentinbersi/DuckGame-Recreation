#pragma once
#include "Thread.h"
#include "BlockingQueue.h"
#include "ActiveSocket.h"
#include "ComReceiver.h"
#include "ComSender.h"
#include "GameStatus.h"
#include "Message.h"

#include <iostream>

class Communicator{
private:
    ActiveSocket skt;
    BlockingQueue<Message> sendQueue;
    BlockingQueue<GameStatus> recvQueue;
    CommunicatorSender sender;
    CommunicatorReceiver receiver;

public:
    explicit Communicator(ActiveSocket&& socket);

    bool trysend(const Message& Message);

    std::optional<GameStatus> tryrecv();

    ~Communicator();
};
