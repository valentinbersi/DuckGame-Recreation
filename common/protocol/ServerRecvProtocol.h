#pragma once

#include <memory>
#include <unordered_map>

#include "ActiveSocket.h"
#include "ClientMessage.h"
#include "GameStatus.h"
#include "ReceiveProtocol.h"

class ServerRecvProtocol: public ReceiveProtocol {
private:
public:
    explicit ServerRecvProtocol(ActiveSocket& socket);

    std::unique_ptr<ClientMessage> receiveMessage();

    ~ServerRecvProtocol() = default;
};
