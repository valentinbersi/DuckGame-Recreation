#pragma once
#include "MessageType.h"

// Sketch muy basico para prueba del protocolo.
struct Message {
    MessageType type;
    explicit Message(MessageType type): type(type) {}
    virtual ~Message() = default;
};
