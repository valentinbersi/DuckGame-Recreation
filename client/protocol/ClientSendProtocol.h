#pragma once
#include "ActiveSocket.h"
#include "Message.h"
#include "SendProtocol.h"
#include "ActiveSocket.h"
#include "GameMessage.h"
#include "LobbyMessage.h"


class ClientSendProtocol: public SendProtocol {
public:
    explicit ClientSendProtocol(ActiveSocket& socket);

    void sendMessage(const Message& message);

    ~ClientSendProtocol() override = default;
};
