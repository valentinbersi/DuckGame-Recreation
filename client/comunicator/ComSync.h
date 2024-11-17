#pragma once

#include "ClientSendProtocol.h"
#include "ClientRecvProtocol.h"
#include "ActiveSocket.h"
#include "ReplyMessage.h"

class CommunicatorSync {
private:
    ClientSendProtocol sendProtocol;
    ClientRecvProtocol recvProtocol;

public:
    CommunicatorSync(ActiveSocket& socket);

    void sendMessage(std::unique_ptr<ClientMessage> message);

    ReplyMessage recvMessage();

    ~CommunicatorSync();
};

