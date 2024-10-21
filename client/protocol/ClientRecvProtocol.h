#pragma once

#include "ActiveSocket.h"
#include "ReceiveProtocol.h"
#include "GameStatus.hpp"

class ClientRecvProtocol : public  ReceiveProtocol{
public:
    ClientRecvProtocol(ActiveSocket&);

    // GameStatus receiveMessage();

    ~ClientRecvProtocol() = default;

};
