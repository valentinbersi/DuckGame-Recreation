#pragma once
#include "MessageType.h"

// Sketch muy basico para prueba del protocolo.
struct Message {
    MessageType type;
    Message(MessageType type): type(type) {}
    virtual ~Message() = default;
};
