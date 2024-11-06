#pragma once
#include <memory>

#include "ActiveSocket.h"
#include "BlockingQueue.h"
#include "Command.h"
#include "GameMapMonitor.h"
#include "Receiver.h"
#include "Sender.h"
#include "ServerMessage.h"

class VirtualClient {
private:
    ActiveSocket skt;
    // mapa de gameloops va aqui, referencia
    // BlockingQueue<std::unique_ptr<Command>>* gameQueue;
    u16 id;
    std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> sendQueue;
    Receiver receiver;
    Sender sender;

public:
    VirtualClient(ActiveSocket socket, GameMapMonitor& monitor, u16 clientID);

    bool isConnected();

    ~VirtualClient();
};
