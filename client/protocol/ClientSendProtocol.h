#pragma once
#include "ClientMessage.h"
#include "../../common/protocol/SendProtocol.h"
#include "../../common/socket/ActiveSocket.h"

class ClientSendProtocol: public SendProtocol {
public:
    explicit ClientSendProtocol(ActiveSocket& socket);

    void sendMessage(const ClientMessage& message);

    ~ClientSendProtocol() = default;
};
