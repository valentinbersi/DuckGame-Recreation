#pragma once
#include <memory>

#include "ActiveSocket.h"
#include "BlockingQueue.h"
#include "ServerMessage.h"
#include "ServerSendProtocol.h"
#include "Thread.h"

class Sender: public Thread {
private:
    ServerSendProtocol sendProtocol;
    std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>>& sendQueue;

public:
    /**
     * Create a new Sender 
     * @param socket The socket to send messages to
     * @param queue The queue to read messages from
     */
    Sender(ActiveSocket& socket,
           std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>>& queue);

    /**
     * Send messages from the queue to the socket
     */
    void run() noexcept override;

    /**
     * Stop the sender
     */
    void stop() override;

    /**
     * Destroy the Sender
     */
    ~Sender();
};
