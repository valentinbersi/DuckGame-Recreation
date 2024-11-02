#pragma once

#include <memory>
#include <unordered_map>

#include "ActiveSocket.h"
#include "GameStatus.h"
#include "ClientMessage.h"
#include "ReceiveProtocol.h"
#include <memory>

class ServerRecvProtocol: public ReceiveProtocol {
private:
public:
    explicit ServerRecvProtocol(ActiveSocket& socket);

    std::unique_ptr<ClientMessage> receiveMessage();

    ~ServerRecvProtocol() = default;
};
