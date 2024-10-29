#pragma once
#include "ClientMessage.h"
struct GameMessage : public ClientMessage
{
    InputAction action;
    GameMessage(InputAction action) : ClientMessage(MessageType::Game), action(action) {}
    ~GameMessage() = default;
};
