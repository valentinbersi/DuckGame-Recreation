#pragma once

#include <memory>
#include "ClientMessage.h"
#include "ActiveSocket.h"
#include "GameStatus.hpp"
#include "ReceiveProtocol.h"
#include <unordered_map>

class ServerRecvProtocol: public ReceiveProtocol {
private:
public:
    explicit ServerRecvProtocol(ActiveSocket& socket);

    ClientMessage receiveMessage();

    ~ServerRecvProtocol() = default;
};
