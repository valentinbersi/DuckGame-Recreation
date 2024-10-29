#pragma once
#include "ClientMessage.h"

struct LobbyMessage : public ClientMessage
{
    LobbyRequest request;
    LobbyMessage(LobbyRequest request) : ClientMessage(MessageType::Lobby), request(request) {}
    ~LobbyMessage() = default;
};
