#pragma once
#include "ClientSendProtocol.h"
#include "MessageType.h"

struct ClientMessage {
public:
    MessageType type;

    explicit ClientMessage(MessageType type): type(type) {}

    virtual void send(ClientSendProtocol& clientProtocol) = 0;

    virtual ~ClientMessage() = default;
};
