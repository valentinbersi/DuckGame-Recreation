#pragma once
#include "Thread.h"
#include "ServerRecvProtocol.h"
#include "BlockingQueue.h"
#include "ClientMessage.h"
#include "LobbyManager.h"
#include "Command.h"
#include <memory>

class Receiver: public Thread{
private:
    ServerRecvProtocol recvProtocol;
    BlockingQueue<std::unique_ptr<Command>>* gameQueue;
    Lobby lobby; 
    // CommnadFactory factory;
public:
    Receiver(ActiveSocket& socket, BlockingQueue<std::unique_ptr<Command>>* queueRecv,
             BlockingQueue<std::unique_ptr<GameStatus>> queueSender /*mapa de partidas.*/);

    virtual void run() override;

    void stop() override;

    ~Receiver();
};


