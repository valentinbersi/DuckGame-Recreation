#pragma once

#include <memory>
#include <unordered_map>

#include "ActiveSocket.h"
#include "ClientMessage.h"
#include "GameMessage.h"
#include "LobbyMessage.h"
#include "ReceiveProtocol.h"

/**
 * Dedicated ServerReceive Protocol
 */
class ServerRecvProtocol: public ReceiveProtocol {
public:
    /**
     * Construct a new ServerRecvProtocol object
     * @param socket the ActiveSocket to receive data from
     */
    explicit ServerRecvProtocol(ActiveSocket& socket);

    /**
     * Receive a GameMessage from the client
     * @return the GameMessage received
     */
    GameMessage receiveGameMessage();

    /**
     * Receive a LobbyMessage from the client
     * @return the LobbyMessage received
     */
    LobbyMessage receiveLobbyMessage();

    /**
     * Default destructor
     */
    ~ServerRecvProtocol() = default;
};
