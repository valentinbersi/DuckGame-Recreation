#pragma once
#include "ClientMessage.h"

struct LobbyMessage : public ClientMessage
{
    LobbyRequest request;
    LobbyMessage(LobbyRequest request) : request(request), ClientMessage(MessageType::Lobby) {}
    ~LobbyMessage() = default;
};

#pragma once
#include "ClientMessage.h"
#include "Types.h"
#include <string>

struct LobbyMessage : public ClientMessage
{
    LobbyRequest request;
    std::string usrName;
    u16 matchId;
    LobbyMessage(LobbyRequest request, std::string name, u16 id) : ClientMessage(MessageType::Lobby), request(request), usrName(name), matchId(id) {}
    ~LobbyMessage() = default;
};
