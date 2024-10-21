#pragma once

#include "ActiveSocket.h"
#include "GameStatus.hpp"
#include "ReceiveProtocol.h"

class ClientRecvProtocol: public ReceiveProtocol {
public:
    explicit ClientRecvProtocol(ActiveSocket&);

    // GameStatus receiveMessage();

    ~ClientRecvProtocol() = default;
};
