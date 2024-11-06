#pragma once
#include <iostream>
#include <queue>

#include "ActiveSocket.h"
#include "BlockingQueue.h"
#include "ClientMessage.h"
#include "ComReceiver.h"
#include "ComSender.h"
#include "GameStatus.h"
#include "ServerMessage.h"
#include "Thread.h"

class Communicator {
private:
    ActiveSocket skt;
    BlockingQueue<std::unique_ptr<ClientMessage>> sendQueue;
    BlockingQueue<std::unique_ptr<ServerMessage>> recvQueue;
    CommunicatorSender sender;
    CommunicatorReceiver receiver;

public:
    explicit Communicator(const std::string& hostname, const std::string& servername);

    bool trysend(std::unique_ptr<ClientMessage> Message);

    std::optional<std::unique_ptr<ServerMessage>> tryrecv();

    std::optional<std::unique_ptr<ServerMessage>> tryRecvLast();

    std::unique_ptr<ServerMessage> recv();

    ~Communicator();
};
