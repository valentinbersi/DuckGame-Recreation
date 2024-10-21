#pragma once

#include "ActiveSocket.h"
#include "ReceiveProtocol.h"

class ClientRecvProtocol : public  ReceiveProtocol{
public:
    ClientRecvProtocol(ActiveSocket&);

    // Snapshot receiveMessage();

    ~ClientRecvProtocol() = default;

};
