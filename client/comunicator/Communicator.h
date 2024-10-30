#pragma once
#include <iostream>

#include "ActiveSocket.h"
#include "BlockingQueue.h"
#include "ComReceiver.h"
#include "ComSender.h"
#include "GameStatus.h"
#include "Message.h"
#include "Thread.h"

class Communicator {
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
