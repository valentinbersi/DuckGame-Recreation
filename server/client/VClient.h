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
    u16 id;
    std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> sendQueue;
    Receiver receiver;
    Sender sender;

public:
    /**
     * Creates a new VirtualClient
     * @param socket The socket of the client
     * @param monitor The monitor of the game
     * @param clientID The id of the client
     */
    VirtualClient(ActiveSocket socket, GameMapMonitor& monitor, u16 clientID);

    /**
     * Checks if connection is still active
     */
    bool isConnected();

    /**
     * Destroys the VirtualClient
     */
    ~VirtualClient();
};
