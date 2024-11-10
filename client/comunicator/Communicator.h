#pragma once
#include <iostream>
#include <queue>

#include "ActiveSocket.h"
#include "BlockingQueue.h"
#include "ClientMessage.h"
#include "ComSync.h"
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
    // CommunicatorSync sync;
    CommunicatorSender sender;
    CommunicatorReceiver receiver;

public:
    explicit Communicator(const std::string& hostname, const std::string& servername);

    void runAsync();

    bool trysend(std::unique_ptr<ClientMessage> message);

    std::optional<GameStatus> tryrecv();

    std::optional<GameStatus> tryRecvLast();

    std::optional<ReplyMessage> tryRecvReply();

    ReplyMessage blockingRecv();

    ~Communicator();
};
