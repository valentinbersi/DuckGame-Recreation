#pragma once
#include "ClientMessage.h"

struct LobbyMessage : public ClientMessage
{
    LobbyRequest request;
    LobbyMessage(LobbyRequest request) : request(request), ClientMessage(MessageType::Lobby) {}
    ~LobbyMessage() = default;
};
