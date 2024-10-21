#pragma once

#include "SendProtocol.h"
#include "ActiveSocket.h"
#include "GameStatus.hpp"
#include <memory>

class ServerSendProtocol: public SendProtocol {
public:
    ServerSendProtocol(ActiveSocket&);

    void sendMessage(std::shared_ptr<GameStatus>& mensaje);

    ~ServerSendProtocol() = default;
};
