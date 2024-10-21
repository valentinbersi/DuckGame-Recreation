#pragma once

#include <memory>

#include "ActiveSocket.h"
#include "GameStatus.hpp"
#include "SendProtocol.h"

class ServerSendProtocol: public SendProtocol {
public:
    explicit ServerSendProtocol(ActiveSocket&);

    void sendMessage(std::shared_ptr<GameStatus>& mensaje);

    ~ServerSendProtocol() = default;
};
