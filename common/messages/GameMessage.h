#pragma once
#include "Message.h"

struct GameMessage : public Message
{
    InputAction action;
    GameMessage(InputAction action) : Message(MessageType::Game), action(action) {}
    ~GameMessage() = default;
};
