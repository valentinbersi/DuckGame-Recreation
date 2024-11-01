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
    BlockingQueue<std::unique_ptr<Message>> sendQueue;
    BlockingQueue<std::unique_ptr<Message>> recvQueue;
    CommunicatorSender sender;
    CommunicatorReceiver receiver;

public:
    explicit Communicator(const std::string& hostname, const std::string& servername);

    bool trysend(std::unique_ptr<Message> Message);

    std::optional<std::unique_ptr<Message>> tryrecv();

    std::queue<std::unique_ptr<Message>> recvAll();

    ~Communicator();
};
