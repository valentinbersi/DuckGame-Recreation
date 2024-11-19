#pragma once

#include "ActiveSocket.h"
#include "ClientRecvProtocol.h"
#include "ClientSendProtocol.h"
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
