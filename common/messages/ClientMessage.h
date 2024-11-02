#pragma once
#include "MessageType.h"
#include "ClientSendProtocol.h"

struct ClientMessage {
public:
    MessageType type;

    explicit ClientMessage(MessageType type) : type(type) {}

    virtual void send(ClientSendProtocol& clientProtocol) = 0;

    virtual ~ClientMessage() = default;
};
