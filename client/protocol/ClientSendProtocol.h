#pragma once
#include "ActiveSocket.h"
#include "GameMessage.h"
#include "LobbyMessage.h"
#include "Message.h"
#include "SendProtocol.h"


class ClientSendProtocol: public SendProtocol {
public:
    explicit ClientSendProtocol(ActiveSocket& socket);

    void sendMessage(const Message& message);

    ~ClientSendProtocol() override = default;
};
