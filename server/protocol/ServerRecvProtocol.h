#pragma once

#include <memory>
#include "Message.h"
#include "ActiveSocket.h"
#include "GameStatus.h"
#include "ReceiveProtocol.h"
#include <unordered_map>

class ServerRecvProtocol: public ReceiveProtocol {
private:
public:
    explicit ServerRecvProtocol(ActiveSocket& socket);

    Message receiveMessage();

    ~ServerRecvProtocol() = default;
};
