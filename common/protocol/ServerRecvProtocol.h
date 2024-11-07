#pragma once

#include <memory>
#include <unordered_map>

#include "ActiveSocket.h"
#include "ClientMessage.h"
#include "GameMessage.h"
#include "LobbyMessage.h"
#include "ReceiveProtocol.h"

class ServerRecvProtocol: public ReceiveProtocol {
private:
public:
    explicit ServerRecvProtocol(ActiveSocket& socket);

    GameMessage receiveGameMessage();

    LobbyMessage receiveLobbyMessage();

    std::unique_ptr<ClientMessage> receiveMessage();

    ~ServerRecvProtocol() = default;
};
