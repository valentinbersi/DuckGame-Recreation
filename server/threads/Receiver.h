#pragma once
#include <memory>

#include "BlockingQueue.h"
#include "Command.h"
#include "GameMapMonitor.h"
#include "LobbyResolver.h"
#include "ServerMessage.h"
#include "ServerRecvProtocol.h"
#include "Thread.h"
#include "CommandFactory.h"

class Receiver: public Thread {
private:
    ServerRecvProtocol recvProtocol;
    BlockingQueue<std::unique_ptr<Command>>* gameQueue;
    const u16& clientID;
    LobbyResolver lobbyResolver;
    static CommandFactory factory;
public:
    Receiver(ActiveSocket& socket,
             std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> queueSender,
             GameMapMonitor& monitor, const u16& clientID);

    void run() noexcept override;

    void stop() override;

    ~Receiver();
};
