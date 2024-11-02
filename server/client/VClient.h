#pragma once
#include <memory>

#include "ActiveSocket.h"
#include "BlockingQueue.h"
#include "Command.h"
#include "ServerMessage.h"
#include "GameMapMonitor.h"
#include "Receiver.h"
#include "Sender.h"

class VirtualClient {
private:
    ActiveSocket skt;
    // mapa de gameloops va aqui, referencia
    BlockingQueue<std::unique_ptr<Command>>* gameQueue;  // No tengo de otra porque aun no se cual
                                                         // es
    std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> sendQueue;
    Receiver receiver;
    Sender sender;

public:
    VirtualClient(ActiveSocket socket, GameMapMonitor& monitor);

    bool isConnected();

    ~VirtualClient();
};
