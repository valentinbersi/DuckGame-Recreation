#pragma once
#include "MessageType.h"


// Sketch muy basico para prueba del protocolo.
struct ClientMessage {
    MessageType type;
    ClientMessage(MessageType type): type(type) {}
    virtual ~ClientMessage() = default;
};
