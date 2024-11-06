#pragma once
#include "MessageType.h"
#include "ServerSendProtocol.h"

struct ServerMessage {
public:
    MessageType type;

    explicit ServerMessage(MessageType type): type(type) {}

    virtual void send(ServerSendProtocol& serverProtocol) = 0;

    virtual ~ServerMessage() = default;
};