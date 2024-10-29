#pragma once
#include "ClientMessage.h"
struct GameMessage : public ClientMessage
{
    InputAction action;
    GameMessage(InputAction action) : action(action), ClientMessage(MessageType::Game) {}
    ~GameMessage() = default;
};
