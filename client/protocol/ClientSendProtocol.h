#pragma once
#include "ActiveSocket.h"
#include "ClientMessage.h"
#include "SendProtocol.h"
#include "ActiveSocket.h"
#include "GameMessage.h"
#include "LobbyMessage.h"


class ClientSendProtocol: public SendProtocol {
public:
    explicit ClientSendProtocol(ActiveSocket& socket);

    void sendMessage(const ClientMessage& message);

    ~ClientSendProtocol() override = default;
};
