#pragma once

#include <memory>
#include <unordered_map>

#include "ActiveSocket.h"
#include "GameStatus.h"
#include "Message.h"
#include "ReceiveProtocol.h"

class ServerRecvProtocol: public ReceiveProtocol {
private:
public:
    explicit ServerRecvProtocol(ActiveSocket& socket);

    Message receiveMessage();

    ~ServerRecvProtocol() = default;
};
