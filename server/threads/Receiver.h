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
    /**
     * Create a new Receiver
     * @param socket The socket to receive messages from
     * @param queueSender Queue need for connections with the lobby
     * @param monitor The monitor to resolve the lobby requests to join Games
     * @param clientID The id of the client
     */
    Receiver(ActiveSocket& socket,
             std::shared_ptr<BlockingQueue<std::shared_ptr<ServerMessage>>> queueSender,
             GameMapMonitor& monitor, const u16& clientID);

    /**
     * Receive messages from the socket and push them to the queue
     */
    void run() noexcept override;

    /**
     * Stop the receiver
     */
    void stop() override;

    /**
     *  Destroy the Receiver
     */
    ~Receiver();
};
