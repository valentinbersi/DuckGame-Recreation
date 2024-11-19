#pragma once
#include <iostream>
#include <memory>
#include <queue>
#include <string>

#include "ActiveSocket.h"
#include "BlockingQueue.h"
#include "ClientMessage.h"
#include "ComReceiver.h"
#include "ComSender.h"
#include "GameStatus.h"
#include "ReplyMessage.h"
#include "ServerMessage.h"
#include "Thread.h"

class Communicator {
private:
    ActiveSocket skt;
    BlockingQueue<std::unique_ptr<ClientMessage>> sendQueue;
    BlockingQueue<ReplyMessage> recvQueueLobby;
    BlockingQueue<GameStatus> recvQueueGame;
    CommunicatorSender sender;
    CommunicatorReceiver receiver;

public:
    explicit Communicator(const std::string& hostname, const std::string& servername);

    bool trysend(std::unique_ptr<ClientMessage> message);

    std::optional<GameStatus> tryrecv();

    std::optional<GameStatus> tryRecvLast();

    std::optional<ReplyMessage> tryRecvReply();

    ReplyMessage blockingRecv();

    ~Communicator();
};
